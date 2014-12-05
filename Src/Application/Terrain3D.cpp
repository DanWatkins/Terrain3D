//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Terrain3D.h"
#include <Core/Core.h>
#include <QuickItems/Camera.h>

namespace t3d
{
	Terrain3D::Terrain3D() :
		//mCamera(this, &mWorld),
		mPreviouslyHadFocus(false)
	{
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

		QuickItems::Camera *camera = this->rootObject()->findChild<QuickItems::Camera*>("t3d_mainCamera");
		camera->setWorld(&mWorld);

		qDebug() << "We got the camera " << camera;
	}


	void Terrain3D::render()
	{
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
				const double mouseSensitivity = 0.1f;
				QVector2D delta = consumeCursorDelta();
				//mCamera.incOrientation(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);

				resetCursorPosition();
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

			/*case Qt::Key_W:
				mCamera.incPosition(speed * mCamera.getForward()); break;
			case Qt::Key_S:
				mCamera.incPosition(speed * -mCamera.getForward()); break;
			case Qt::Key_A:
				mCamera.incPosition(speed * -mCamera.getRight()); break;
			case Qt::Key_D:
				mCamera.incPosition(speed * mCamera.getRight()); break;

			case Qt::Key_Z:
				mCamera.setMode(Mode::Normal); break;
			case Qt::Key_X:
				mCamera.setMode(Mode::WireFrame); break;
			*/
		}
	}
}
