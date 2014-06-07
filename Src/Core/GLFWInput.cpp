//=======================================================================================================================|
// Created 2013.11.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "GLFWInput.h"

namespace t3d
{
	std::vector<OpenGLWindow*> GLFWInput::mWindows;


	GLFWInput& GLFWInput::instance()
	{
		static GLFWInput instance;

		return instance;
	}

	
	void GLFWInput::addWindow(OpenGLWindow *window)
	{
		//ensure @window is not already a registered window
		for (GLuint n=0; n<mWindows.size(); n++)
		{
			if (window == mWindows[n])
				return;
		}

		mWindows.push_back(window);
	}

	
	void GLFWInput::keyboardCallback(int action, int key, int a, int b, int c)
	{
		for (GLuint n=0; n<mWindows.size(); n++)
			mWindows[n]->onKey(key, action);
	}

	
	void GLFWInput::windowResizeCallback(GLFWwindow *window, int width, int height)
	{
		//only tell the window that matches @window there was a resize
		for (GLuint n=0; n<mWindows.size(); n++)
		{
			if (mWindows[n]->isWindow(window))
			{
				mWindows[n]->_onResize(width, height);
				return;
			}
		}
	}
};