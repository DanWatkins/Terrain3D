//=======================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _GL_ZOMBIES_H
#define _GL_ZOMBIES_H

#include "Main.h"
#include "./Core/OpenGLWindow.h"

namespace t3d
{
	/**
	 * Represents the main application
	 */
	class Terrain3D : public OpenGLWindow
	{
	private:
		void onStartup();
		void onUpdate(Double currentTime);
		void onKey(Int key, Int action);
		void onResize(Int width, Int height);
		void onTerminate();

		void loadShaders();

	public:
		Terrain3D();
	};
};

#endif

