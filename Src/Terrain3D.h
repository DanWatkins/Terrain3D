//=======================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _GL_TERRAIN3D_H
#define _GL_TERRAIN3D_H

#include "Main.h"
#include "./Core/OpenGLWindow.h"
#include "./World/World.h"
#include "./World/Camera.h"
#include "World/HeightMap.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace t3d
{
	struct UniformLocations
	{
		Uint matrix_cameraToClip;
		Uint matrix_modelToWorld;
		Uint matrix_worldToCamera;

	};


	/**
	 * Represents the main application
	 */
	class Terrain3D : public OpenGLWindow
	{
	private:
		Uint mProgram;
		Uint mVbo, mIbo, mVao;
		UniformLocations mUniformLocations;

		World mWorld;
		Camera mCamera;

	private:
		void onStartup();
		void onUpdate(Double currentTime);
		void onKey(Int key, Int action);
		void onResize(Int width, Int height);
		void onTerminate();

		void loadShaders();
		void updateKeys();

	public:
		Terrain3D();
	};
};

#endif

