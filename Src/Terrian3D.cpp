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
		mCamera(this, &mWorld)
	{
	}


	void Terrain3D::initialize()
	{
		mWorld.init();
		mCamera.init();
		mCamera.resize(width(), height());
		resetCursorPosition();
	}
	 
	
	void Terrain3D::render()
	{
		OpenGLWindow::render();

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		const qreal retinaScale = devicePixelRatio();
		glViewport(0, 0, width() * retinaScale, height() * retinaScale);

		mCamera.render();

		const double mouseSensitivity = 0.1f;
		QVector2D delta = getCursorDelta();
		mCamera.incOrientation(delta.x()*mouseSensitivity, delta.y()*mouseSensitivity);
		resetCursorPosition();		
	}


	void Terrain3D::keyPressEvent(QKeyEvent *ev)
	{
		const float speed = 3.0f;
		const float adj = 0.5f;

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

			case Qt::Key_Z:
				mCamera.setMode(Mode::Normal); break;
			case Qt::Key_X:
				mCamera.setMode(Mode::WireFrame); break;
		}
	}
};