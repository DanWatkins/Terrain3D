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
		/**
		 * @returns A pointer to the internal GLFW window object
		 */
		const GLFWwindow *getWindow() const { return mWindow; }

	public:
		friend GLFWInput;

		OpenGLWindow();

		/**
		 * Configures a GLFW window.
		 *
		 * @param width the width in pixels of the OpenGL rendering area
		 * @param height the height in pixels of the OpenGL rendering area
		 * @param title the title of the window
		 */
		int init(int width=gDefaultWindowWidth, int height=gDefaultWindowHeight, const String &title=gWindowTitle);

		/**
		 * @returns Width in pixels of the window
		 */
		int getWidth() const { return mWidth; }

		/**
		 * @returns Height in pixels of the window
		 */
		int getHeight() const { return mHeight; }

		/**
		 * @returns Title of the window
		 */
		String getTitle() const { return mTitle; }

		/**
		 * @param window The window to check
		 * @returns True if the specified window is the same as the internal window
		 */
		bool isWindow(GLFWwindow *window) const { return window == mWindow; }

		/**
		 * @returns TODO what
		 */
		Vec2f getAspectScale() const { return mAspectScale; }

		/**
		 * Sets the zoom which is used for calculating the aspect ratio for the OpenGL context.
		 * 
		 * @param zoom the zoom factor
		 */
		void setZoom(Vec2f zoom);

		/**
		 *
		 */
		void addZoom(Vec2f zoom);

		/**
		 * Sets
		 */
		void terminate() { mShouldTerminate = true; }


	protected:
		/**
		 *
		 */
		virtual void onStartup() = 0;

		/**
		 *
		 */
		virtual void onUpdate(double timeSinceStartup) = 0;

		/**
		 *
		 */
		virtual void onKey(int key, int action) = 0;

		/**
		 *
		 */
		virtual void onResize(int width, int height) = 0;

		/**
		 *
		 */
		virtual void onTerminate() = 0;

		/**
		 *
		 */
		void printContextInformation() const;


	private:
		/**
		 *
		 */
		void _onResize(int width, int height);
	};
};


#endif

