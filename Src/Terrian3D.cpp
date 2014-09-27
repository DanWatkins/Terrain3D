//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Terrain3D.h"
#include "./Core/Core.h"
#include "Core\Sprite.h"
#include "Core\Image.h"
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
		//glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetCursorPos(getWindow(), 0.0, 0.0);

		mWorld.init();
		mCamera.init(&mWorld);
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
		double mouseX, mouseY;
		//glfwGetCursorPos(getWindow(), &mouseX, &mouseY);
		//mCamera.incOrientation((float)(mouseSensitivity*mouseX), (float)(mouseSensitivity*mouseY));
		//glfwSetCursorPos(getWindow(), 0.0, 0.0);

		mCamera.render();
	}


	void onKey(int key, int action)
	{
		const float speed = 0.19f;

		/*switch (key)
		{
			case GLFW_KEY_ESCAPE:
				terminate(); break;

			case GLFW_KEY_W:
				mCamera.incPosition(speed * mCamera.getForward()); break;
			case GLFW_KEY_S:
				mCamera.incPosition(speed * -mCamera.getForward()); break;
			case GLFW_KEY_A:
				mCamera.incPosition(speed * -mCamera.getRight()); break;
			case GLFW_KEY_D:
				mCamera.incPosition(speed * mCamera.getRight()); break;

			case GLFW_KEY_R:
			{
				mWorld.init();
				mCamera.init(&mWorld);

				break;
			}
		}*/
	}

	
	void onResize(int width, int height)
	{
		//glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}


	void onTerminate()
	{
	}
};