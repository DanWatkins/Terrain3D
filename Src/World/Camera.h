//=======================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _t3d_CAMERA_H
#define _t3d_CAMERA_H

#include "../Main.h"
#include "../Core/OpenGLWindow.h"
#include "HeightMap.h"
#include "World.h"

namespace t3d
{
	class Camera
	{
	private:
		struct RenderData
		{
			Uint vao_terrain;
			Uint indexCount;
		} mRenderData;


	private:
		World *mWorld;

		void uploadTerrainData(HeightMap &heightMap);

	public:
		void init(World *world);
		void render();
	};
};

#endif

