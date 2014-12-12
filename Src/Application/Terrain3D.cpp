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

		mWorld.init();
		//mCamera.init();
		//mCamera.resize(width(), height());

		connect(&backgroundUpdater, &BackgroundUpdater::needsUpdate,
				this, &Terrain3D::willUpdate);
		backgroundUpdater.start();
	}


	void Terrain3D::settingsValueUpdated(Settings::Key key,
										 const QVariant &newValue,
										 const QVariant &oldValue)
	{
		typedef Settings::Key key_t;

		switch (key)
		{
			case key_t::KeyShowHud: break;

			//graphics
			case key_t::KeyWireframe:
			{
				typedef World::Terrain::Mode Mode;
				mCamera.toStrongRef()->setMode(newValue.toBool() ?
												Mode::WireFrame : Mode::Normal);
				break;
			}
		}
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
			case Qt::Key_Escape:
				close(); break;
			case Qt::Key_F1:
				setCapturesCursor(!capturesCursor()); break;
			case Qt::Key_F2:
				QWindow::showNormal(); break;
			case Qt::Key_F3:
				QWindow::showFullScreen(); break;
		}
	}
}
