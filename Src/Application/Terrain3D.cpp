//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Terrain3D.h"
#include <Core/Core.h>
#include <QuickItems/CameraItem.h>

namespace t3d
{
	Terrain3D::Terrain3D(Settings *mainSettings) :
		mPreviouslyHadFocus(false),
		mNeedsRestart(false),
		mMainSettings(mainSettings)
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
		QSurfaceFormat format;
		format.setMajorVersion(4);
		format.setMinorVersion(2);
		format.setProfile(QSurfaceFormat::CompatibilityProfile);
		setFormat(format);

		setPersistentOpenGLContext(true);
		setPersistentSceneGraph(true);

		setResizeMode(QQuickView::SizeRootObjectToView);
		setSource(QUrl("qrc:///main.qml"));

		loadUserSettings();

		mWorld.init();
		//mCamera.init();
		//mCamera.resize(width(), height());

		connect(&backgroundUpdater, &BackgroundUpdater::needsUpdate,
				this, &Terrain3D::willUpdate);
		backgroundUpdater.start();
	}


	void Terrain3D::loadUserSettings()
	{

	}


	void Terrain3D::restart()
	{
		QQuickView::close();
		mNeedsRestart = true;
	}


	void Terrain3D::toggleFullscreen()
	{
		if (QWindow::visibility() == QWindow::FullScreen)
			QWindow::showNormal();
		else
			QWindow::showFullScreen();
	}


	void Terrain3D::toggleCaptureCursor()
	{
		setCapturesCursor(!capturesCursor());
	}


	void Terrain3D::willUpdate()
	{
		if (mCamera.isNull())
		{
			if (auto camera = this->rootObject()->findChild<QuickItems::CameraItem*>("t3d_mainCamera"))
			{
				camera->setWorld(&mWorld);
				mCamera = camera->camera();
			}
		}

		updateCursorPos();
	}


	void Terrain3D::updateCursorPos()
	{
		if (!capturesCursor() && mouseButtonLeftPressed() == false)
			return;

		if (QWindow::isActive())
		{
			if (!mPreviouslyHadFocus)
			{
				resetCursorPosition();
			}
			else
			{
				if (mCamera.toStrongRef())
				{
					const double mouseSensitivity = 0.1f;
					QVector2D delta = consumeCursorDelta();
					mCamera.toStrongRef()->incOrientation(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);

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


	void Terrain3D::keyPressEvent(QKeyEvent *ev)
	{
		QQuickView::keyPressEvent(ev);

		using namespace World::Terrain;
		const float speed = 1.75f;

		//update the camera
		if (auto cameraPtr = mCamera.toStrongRef())
		{
			switch (ev->key())
			{
				case Qt::Key_W:
					cameraPtr->incPosition(speed * cameraPtr->getForward()); break;
				case Qt::Key_S:
					cameraPtr->incPosition(speed * -cameraPtr->getForward()); break;
				case Qt::Key_A:
					cameraPtr->incPosition(speed * -cameraPtr->getRight()); break;
				case Qt::Key_D:
					cameraPtr->incPosition(speed * cameraPtr->getRight()); break;

				case Qt::Key_Z:
					cameraPtr->setMode(Mode::Normal); break;
				case Qt::Key_X:
					cameraPtr->setMode(Mode::WireFrame); break;
			}
		}

		switch (ev->key())
		{
			//quit
			case Qt::Key_Escape:
				close(); break;

			//toggle cursor capture
			case Qt::Key_F1:
				toggleCaptureCursor(); break;

			//restart
			case Qt::Key_F5:
				requestRestart(); break;

			//toggle settings menu
			case Qt::Key_F10:
				emit toggleSettingsMenu(); break;

			//toggle fullscreen
			case Qt::Key_F11: toggleFullscreen(); break;
		}
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
				Vec3f c = mCamera.toStrongRef()->getPosition();
				mCamera.toStrongRef()->setPosition(Vec3f(value.toFloat(), c.y, c.z));
				break;
			}

			CASE(GraphicsCameraPositionY) {
				Vec3f c = mCamera.toStrongRef()->getPosition();
				mCamera.toStrongRef()->setPosition(Vec3f(c.x, value.toFloat(), c.z));
				break;
			}

			CASE(GraphicsCameraPositionZ) {
				Vec3f c = mCamera.toStrongRef()->getPosition();
				mCamera.toStrongRef()->setPosition(Vec3f(c.x, c.y, value.toFloat()));
				break;
			}

			CASE(GraphicsCameraFOV) {
				mCamera.toStrongRef()->setFieldOfView(value.toFloat());
				break;
			}

			CASE(GraphicsCameraLOD) {
				//TODO implement a LOD factor!
				break;
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
}
