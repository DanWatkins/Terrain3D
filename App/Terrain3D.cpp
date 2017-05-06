//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtQml/QQmlContext>
#include <QtConcurrent/QtConcurrent>

#include "Terrain3D.h"
#include "QuickItems/CameraItem.h"
#include <Terrain3D/Core/Core.h>

namespace t3d
{
//========================================
// Public
//========================================
	Terrain3D::Terrain3D(Settings *mainSettings) :
		mPreviouslyHadFocus(false),
		mNeedsRestart(false),
		mMainSettings(mainSettings),
		mCameraItem(nullptr),
		mFPSCounter(1000, 500)
	{
		mMainSettings->addListener(this);
	}


	Terrain3D::~Terrain3D()
	{
		backgroundUpdater.requestInterruption();
		backgroundUpdater.wait(1000);
	}


	void Terrain3D::init()
	{
        vbase::Loadable::Begin b(this);
        pIsLoading.addOnChangedListener([this]
		{
			emit isLoadingChanged();
		});

		setResizeMode(QQuickView::SizeRootObjectToView);
		setSource(QUrl("qrc:///main.qml"));

        QObject::connect(this, &QQuickWindow::sceneGraphInitialized, [this]()
        {
            mCameraItem = rootObject()->findChild<QuickItems::CameraItem*>("t3d_mainCamera");
            mCamera = mCameraItem->createCamera();

            if (auto camera = mCamera.lock())
            {
                loadUserSettings();
                mOpenGLTaskQueue.init();
                mEnvironment.init();
                camera->setEnvironment(&mEnvironment);
                camera->init();
                camera->prepareForRendering();
            }
            else
            {
                qFatal("Null camera instance");
                return;
            }

            connect(&backgroundUpdater, &BackgroundUpdater::needsUpdate,
                    this, &Terrain3D::willUpdate);
            backgroundUpdater.start();

            QObject::connect(this, &QQuickView::beforeRendering, [this]
            {
                mFPSCounter.update();
                mOpenGLTaskQueue.runTasks();

                if (pIsLoading)
                    return;
            });

            QObject::connect(&mFPSCounter, &FPSCounter::fpsChanged, [this]() {
                emit fpsChanged();
            });

			mCamera.lock()->pPos.addOnChangedListener([this] {
                emit cameraPosChanged();
            });

            mEnvironment.pIsLoading.addOnChangedListener([this] {
                emit this->isLoadingChanged();
            });

            emit cameraPosChanged();
        });

        QWindow::show();
	}


	void Terrain3D::toggleCaptureCursor()
	{
		setCapturesCursor(!capturesCursor());
	}


	void Terrain3D::toggleFullscreen()
	{
		if (QWindow::visibility() == QWindow::FullScreen)
			QWindow::showNormal();
		else
			QWindow::showFullScreen();

		mMainSettings->setValue(Settings::Key::GraphicsScreenIsFullscreen,
								QWindow::visibility() == QWindow::FullScreen);

		emit refreshSettingsMenu();
	}


	void Terrain3D::toggleWireframe()
	{
		world::Camera *camera = mCamera.lock().get();

		using namespace world::terrain;
		camera->mode() == Mode::Normal ?
					camera->setMode(Mode::WireFrame) :
					camera->setMode(Mode::Normal);

		mMainSettings->setValue(Settings::Key::GraphicsCameraWireframe,
								camera->mode() == Mode::WireFrame);

		emit refreshSettingsMenu();
	}


	void Terrain3D::settingsValueChanged(Settings::Key key, const QVariant &value)
	{
		#define CASE(k) case Settings::k:

		switch (key)
		{
			//graphics
			CASE(GraphicsScreenResolutionWidth) {
				//QWindow::resize(value.toInt(), QWindow::height());
				break;
			}

			CASE(GraphicsScreenResolutionHeight) {
				//QWindow::resize(QWindow::width(), value.toInt());
				break;
			}

			CASE(GraphicsScreenIsFullscreen) {
				//value.toBool() ? QWindow::showFullScreen() : QWindow::showNormal();
				break;
			}

			CASE(GraphicsCameraPositionX) {
				mCamera.lock()->pPos().x = value.toFloat();
				break;
			}

			CASE(GraphicsCameraPositionY) {
				mCamera.lock()->pPos().y = value.toFloat();
				break;
			}

			CASE(GraphicsCameraPositionZ) {
				mCamera.lock()->pPos().z = value.toFloat();
				break;
			}

			CASE(GraphicsCameraFOV) {
				if (auto camera = mCamera.lock())
                    camera->pFieldOfView = value.toFloat();
				break;
			}

            CASE(GraphicsCameraLODFactor) {
				if (auto camera = mCamera.lock())
					camera->terrainRenderer().pLodFactor = value.toFloat();
				break;
			}

            CASE(GraphicsCameraLODNear) {
                if (auto camera = mCamera.lock())
                    camera->terrainRenderer().pLodNear = value.toFloat();
                break;
            }

            CASE(GraphicsCameraLODFar) {
                if (auto camera = mCamera.lock())
                    camera->terrainRenderer().pLodFar = value.toFloat();
                break;
            }

			CASE(GraphicsCameraWireframe) {
				if (auto camera = mCamera.lock())
					camera->setMode(value.toBool()
											   ? world::terrain::Mode::WireFrame :
												 world::terrain::Mode::Normal);
				break;
			}


			//world
			CASE(WorldGeneratorSize) {
				mEnvironment.pSize = value.toInt();
				break;
			}

			CASE(WorldGeneratorTextureMapResolution) {
				mEnvironment.terrainData().pTextureMapResolution = value.toInt();
				break;
			}

			CASE(WorldGeneratorSeed) {
				mEnvironment.pSeed = value.toInt();
				break;
			}

			CASE(WorldGeneratorFaultCount) {
				mEnvironment.pFaultCount = value.toInt();
				break;
			}

			CASE(WorldGeneratorSmoothing) {
				mEnvironment.pSmoothing = value.toFloat();
				break;
			}

			CASE(WorldTerrainLightIntensity) {
				mEnvironment.pLightIntensity = value.toFloat();
				break;
			}

			CASE(WorldTerrainHeightScale) {
				if (auto camera = mCamera.lock())
					mEnvironment.terrainData().pHeightScale = value.toFloat();
				break;
			}

			CASE(WorldTerrainChunkSize) {
				if (auto camera = mCamera.lock())
					mEnvironment.terrainData().pChunkSize = value.toInt();
				break;
			}

			CASE(WorldTerrainSpanSize) {
				if (auto camera = mCamera.lock())
					mEnvironment.terrainData().pSpanSize = value.toInt(); 
				break;
			}
		}

		#undef CASE
	}


	void Terrain3D::settingsQueueFinishedApplying()
	{
		refresh();
	}


//========================================
// Private
//========================================
	void Terrain3D::focusOutEvent(QFocusEvent *ev)
	{
		OpenGLQuickView::focusOutEvent(ev);
		mMovementKeys.clear();
	}


	void Terrain3D::keyPressEvent(QKeyEvent *ev)
	{
		OpenGLQuickView::keyPressEvent(ev);
		using namespace world::terrain;

		switch (ev->key())
		{
			//quit
			case Qt::Key_Escape:
				close(); break;

			case Qt::Key_X:
			{
				if (!pIsLoading)	//TODO need a way to lock the loading state so that another thread can't start loading after this line executes
					if (!mCamera.expired() && !mCameraItem->isFrozen())
						toggleWireframe();
				break;
			}

			//toggle cursor capture
			case Qt::Key_F1:
				toggleCaptureCursor();
				break;

			//restart
			case Qt::Key_F5:
				requestRestart();
				break;

			//reload shaders
			case Qt::Key_F6:
				reloadShaders();
				break;

			//toggle settings menu
			case Qt::Key_F10:
				if (!pIsLoading) emit toggleSettingsMenu();
				break;

			//toggle fullscreen
			case Qt::Key_F11:
				toggleFullscreen();
				break;

			case Qt::Key_W:
				mMovementKeys.w = true; break;
			case Qt::Key_A:
				mMovementKeys.a = true; break;
			case Qt::Key_S:
				mMovementKeys.s = true; break;
			case Qt::Key_D:
				mMovementKeys.d = true; break;
		}
	}


	void Terrain3D::keyReleaseEvent(QKeyEvent *ev)
	{
		OpenGLQuickView::keyReleaseEvent(ev);
		
		switch (ev->key())
		{
		case Qt::Key_W:
			mMovementKeys.w = false; break;
		case Qt::Key_A:
			mMovementKeys.a = false; break;
		case Qt::Key_S:
			mMovementKeys.s = false; break;
		case Qt::Key_D:
			mMovementKeys.d = false; break;
		}
	}


	void Terrain3D::updateCursorPos()
	{
		if (!mCamera.expired() && !mCameraItem->isFrozen())
		{
			float speed = 0.5f;

			if (mMovementKeys.w)
				mCamera.lock()->pPos += (speed * mCamera.lock()->forward());
			if (mMovementKeys.s)
				mCamera.lock()->pPos += (speed * -mCamera.lock()->forward());
			if (mMovementKeys.a)
				mCamera.lock()->pPos += (speed * -mCamera.lock()->right());
			if (mMovementKeys.d)
				mCamera.lock()->pPos += (speed * mCamera.lock()->right());
		}

		if (mCameraItem->isFrozen() || (!capturesCursor() && mouseButtonLeftPressed() == false))
			return;

		if (QWindow::isActive())
		{
			if (!mPreviouslyHadFocus)
			{
				resetCursorPosition();
			}
			else
			{
				if (!mCamera.expired())
				{
                    const float mouseSensitivity = 0.001f;
					QPoint delta = consumeCursorDelta();
					mCamera.lock()->pOrientationAngle += Vec2f(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);

					resetCursorPosition();
				}
			}

			mPreviouslyHadFocus = true;
		}
		else
		{
			mPreviouslyHadFocus = false;
		}
	}


	void Terrain3D::loadUserSettings()
	{
		const QMetaObject &mo = Settings::staticMetaObject;
		const QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));

		//loop through every Settings::Key and tell ourself that a value has
		//changed to effectively load the value
		for (int i=0; i<me.keyCount(); i++)
		{
			Settings::Key key = static_cast<Settings::Key>(me.value(i));
			settingsValueChanged(key, mMainSettings->value(key));
		}
	}


	void Terrain3D::refresh()
	{
		QtConcurrent::run([this]
		{
            vbase::Loadable::Begin b(this);
			mEnvironment.refresh();
			
			mOpenGLTaskQueue.addTask([this](core::OpenGLFunctions*)
			{
				if (auto camera = mCamera.lock())
					camera->refresh();
			});
		});
	}


//========================================
// Public Slots
//========================================
	void Terrain3D::willUpdate()
	{
		if (mCameraItem == nullptr)
		{
			//TODO redundant?
			mCameraItem = rootObject()->findChild<QuickItems::CameraItem*>("t3d_mainCamera");
		}
		else if (!pIsLoading)
		{
			updateCursorPos();
		}
	}
}
