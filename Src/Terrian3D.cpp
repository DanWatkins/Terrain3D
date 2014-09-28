//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Terrain3D.h"
#include "./Core/Core.h"
#include "Core/Sprite.h"
#include "Core/Image.h"
#include "Core/SpriteSheet.h"
#include "Core/Font.h"

namespace t3d
{
	Terrain3D::Terrain3D() :
		mCamera(this)
	{
	}


	void Terrain3D::initialize()
	{
		mWorld.init();
		mCamera.init(&mWorld);
		resetCursor();
	}

	
	void Terrain3D::render()
	{
		OpenGLWindow::render();

		static const float clearColor[] = { 1.0f, 1.0f, 0.9f, 1.0f };
		static const float one[] { 1.0f };
		glClearBufferfv(GL_COLOR, 0, clearColor);
		glClearBufferfv(GL_DEPTH, 0, one);

		const qreal retinaScale = devicePixelRatio();
		glViewport(0, 0, width() * retinaScale, height() * retinaScale);

		//check for mouse changes
		const double mouseSensitivity = 0.05f;
		
		QVector2D delta = cursorDelta();
		mCamera.incOrientation(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);
		resetCursor();

		mCamera.render();
	}


	void Terrain3D::keyPressEvent(QKeyEvent *ev)
	{
		const float speed = 0.19f;

		switch (ev->key())
		{
			case Qt::Key_Escape:
				close(); break;

			case Qt::Key_W:
				mCamera.incPosition(speed * mCamera.getForward()); break;
			case Qt::Key_S:
				mCamera.incPosition(speed * -mCamera.getForward()); break;
			case Qt::Key_A:
				mCamera.incPosition(speed * -mCamera.getRight()); break;
			case Qt::Key_D:
				mCamera.incPosition(speed * mCamera.getRight()); break;

			case Qt::Key_R:
			{
				mWorld.init();
				mCamera.init(&mWorld);

				break;
			}
		}
	}


	QVector2D Terrain3D::cursorDelta()
	{
		double deltaX = QCursor::pos().x() - width()/2;
		double deltaY = QCursor::pos().y() - height()/2;

		return QVector2D(deltaX, deltaY);
	}


	void Terrain3D::resetCursor()
	{
		QCursor::setPos(width()/2, height()/2);
	}
};