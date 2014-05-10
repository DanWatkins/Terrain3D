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
			Uint program;
			Uint vao_terrain;
			Uint indexCount;

			Int uloc_translationMat;
		} mRenderData;

		Vec3f mTranslateAmount;
		Vec3f mScaleAmount;

		Float mZoomFactor;


	private:
		World *mWorld;

		void uploadTerrainData(HeightMap &heightMap);

	public:
		Camera() : mScaleAmount(1.0f, 1.0f, 1.0f), mZoomFactor(1.0f) {}

		void init(Uint program, World *world);
		void render();

		void setZoom(Float zoomFactor) { mZoomFactor = zoomFactor; }
		void incZoom(Float zoomFactor) { mZoomFactor += zoomFactor; }

		//TODO these should probably be reomoved from the public API
		void translate(Vec3f amount) { mTranslateAmount += amount; }
		void scale(Vec3f amount) { mScaleAmount +=amount; }
	};
};

#endif

