//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Terrain3D.h"
#include <Core/Core.h>
#include <QuickItems/CameraItem.h>
#include <QtQml\QQmlContext>

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
		setResizeMode(QQuickView::SizeRootObjectToView);
		setSource(QUrl("qrc:///main.qml"));

		mCameraItem = rootObject()->findChild<QuickItems::CameraItem*>("t3d_mainCamera");
		mCamera = mCameraItem->createCamera();

		loadUserSettings();
		mEnvironment.init(buildWorldConfiguration());
		mCamera.lock()->setEnvironment(&mEnvironment);
		mCamera.lock()->init();

		connect(&backgroundUpdater, &BackgroundUpdater::needsUpdate,
				this, &Terrain3D::willUpdate);
		backgroundUpdater.start();

		QObject::connect(this, &QQuickView::beforeRendering,
						 this, &Terrain3D::beforeRendering);

		QObject::connect(&mFPSCounter, &FPSCounter::fpsChanged,
						 this, &Terrain3D::onFpsChanged);

		QObject::connect(mCamera.lock().get(), &world::Camera::posChanged,
						 this, &Terrain3D::onPosChanged);

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
				QWindow::resize(value.toInt(), QWindow::height());
				break;
			}

			CASE(GraphicsScreenResolutionHeight) {
				QWindow::resize(QWindow::width(), value.toInt());
				break;
			}

			CASE(GraphicsScreenIsFullscreen) {
				value.toBool() ? QWindow::showFullScreen() : QWindow::showNormal();
				break;
			}

			CASE(GraphicsCameraPositionX) {
				Vec3f c = mCamera.lock()->position();
				mCamera.lock()->setPosition(Vec3f(value.toFloat(), c.y, c.z));
				break;
			}

			CASE(GraphicsCameraPositionY) {
				Vec3f c = mCamera.lock()->position();
				mCamera.lock()->setPosition(Vec3f(c.x, value.toFloat(), c.z));
				break;
			}

			CASE(GraphicsCameraPositionZ) {
				Vec3f c = mCamera.lock()->position();
				mCamera.lock()->setPosition(Vec3f(c.x, c.y, value.toFloat()));
				break;
			}

			CASE(GraphicsCameraFOV) {
				mCamera.lock()->setFieldOfView(value.toFloat());
				break;
			}

			CASE(GraphicsCameraLOD) {
				mCamera.lock()->setLodFactor(value.toFloat());
				break;
			}
			CASE(GraphicsCameraWireframe) {
				mCamera.lock()->setMode(value.toBool()
											   ? world::terrain::Mode::WireFrame :
												 world::terrain::Mode::Normal);
			}


			//world
			CASE(WorldGeneratorSize) {
				//TODO
				break;
			}

			CASE(WorldGeneratorTextureMapResolution) {
				//TODO
				break;
			}

			CASE(WorldGeneratorSeed) {
				//TODO
				break;
			}

			CASE(WorldTerrainSpacing) {
				//TODO
				break;
			}

			CASE(WorldTerrainHeightScale) {
				//TODO
				break;
			}

			CASE(WorldTerrainBlockSize) {
				//TODO
				break;
			}

			CASE(WorldTerrainSpanSize) {
				//TODO
				break;
			}
		}

		#undef CASE
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
				if (!mCamera.expired() && !mCameraItem->isFrozen())
					toggleWireframe();

				break;
			}

			//toggle cursor capture
			case Qt::Key_F1:
				toggleCaptureCursor(); break;

			//restart
			case Qt::Key_F5:
				requestRestart(); break;

			//reload shaders
			case Qt::Key_F6:
				reloadShaders(); break;

			//toggle settings menu
			case Qt::Key_F10:
				emit toggleSettingsMenu(); break;

			//toggle fullscreen
			case Qt::Key_F11: toggleFullscreen(); break;

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
				mCamera.lock()->incPosition(speed * mCamera.lock()->forward());
			if (mMovementKeys.s)
				mCamera.lock()->incPosition(speed * -mCamera.lock()->forward());
			if (mMovementKeys.a)
				mCamera.lock()->incPosition(speed * -mCamera.lock()->right());
			if (mMovementKeys.d)
				mCamera.lock()->incPosition(speed * mCamera.lock()->right());
		}

		if (mCameraItem->isFrozen() || !capturesCursor() && mouseButtonLeftPressed() == false)
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
					const float mouseSensitivity = 0.1f;
					QVector2D delta = consumeCursorDelta();
					mCamera.lock()->incOrientation(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);

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
		QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));

		//loop through every Settings::Key and tell ourself that a value has
		//changed to effectively load the value
		for (int i=0; i<me.keyCount(); i++)
		{
			Settings::Key key = static_cast<Settings::Key>(me.value(i));
			settingsValueChanged(key, mMainSettings->value(key));
		}
	}


	world::Environment::Configuration Terrain3D::buildWorldConfiguration()
	{
		typedef Settings::Key key;
		world::Environment::Configuration config;

		config.generatorSize = mMainSettings->value(key::WorldGeneratorSize).toInt();
		config.generatorTextureMapResolution = mMainSettings->value(key::WorldGeneratorTextureMapResolution).toInt();
		config.generatorSmoothing = mMainSettings->value(key::WorldGeneratorSmoothing).toFloat();
		config.generatorFaultCount = mMainSettings->value(key::WorldGeneratorFaultCount).toInt();
		config.generatorSeed = mMainSettings->value(key::WorldGeneratorSeed).toInt();
		config.generatorLightIntensity = mMainSettings->value(key::WorldTerrainLightIntensity).toFloat();

		config.terrainBlockSize = mMainSettings->value(key::WorldTerrainBlockSize).toInt();
		config.terrainHeightScale = mMainSettings->value(key::WorldTerrainHeightScale).toFloat();
		config.terrainSpacing = mMainSettings->value(key::WorldTerrainSpacing).toFloat();
		config.terrainSpanSize = mMainSettings->value(key::WorldTerrainSpanSize).toInt();

		return config;
	}


//========================================
// Public Slots
//========================================
	void Terrain3D::willUpdate()
	{
		if (mCameraItem == nullptr)
		{
			mCameraItem = rootObject()->findChild<QuickItems::CameraItem*>("t3d_mainCamera");
		}
		else
		{
			updateCursorPos();
		}
	}


	void Terrain3D::beforeRendering()
	{
		mFPSCounter.update();
		glClearColor(1.0f, 0.0f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}