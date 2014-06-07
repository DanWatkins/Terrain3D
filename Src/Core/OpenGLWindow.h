//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _OPENGL_WINDOW_H
#define _OPENGL_WINDOW_H

#include "Core.h"

namespace t3d
{
	class GLFWInput;



	/**
	 * Creates a cross-platform OpenGL 4.x rendering context
	 * Provides a runtime loop and keyboard input callbacks
	 * Class is intended to be inherited from by client applications
	 */
	class OpenGLWindow
	{
	private:
		int mWidth, mHeight;
		String mTitle;
		GLFWwindow *mWindow;
		Vec2f mAspectScale, mZoom;
		bool mShouldTerminate;

	protected:
		GLFWwindow *getWindow() { return mWindow; }

	public:
		friend GLFWInput;

		OpenGLWindow();
		int init(int width=gDefaultWindowWidth, int height=gDefaultWindowHeight, const String &title=gWindowTitle);

		int getWidth() const { return mWidth; }
		int getHeight() const { return mHeight; }
		String getTitle() const { return mTitle; }
		bool isWindow(GLFWwindow *window) const { return window == mWindow; }
		Vec2f getAspectScale() const { return mAspectScale; }

		void setZoom(Vec2f zoom);
		void addZoom(Vec2f zoom);

		void terminate() { mShouldTerminate = true; }

	protected:
		virtual void onStartup() = 0;
		virtual void onUpdate(double timeSinceStartup) = 0;
		virtual void onKey(int key, int action) = 0;
		virtual void onResize(int width, int height) = 0;
		virtual void onTerminate() = 0;

		void printContextInformation() const;

	private:
		void _onResize(int width, int height);
	};
};


#endif

