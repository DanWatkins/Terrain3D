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
		Vec3f mRotationAmount;

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
		void scale(Vec3f amount) { mScaleAmount += amount; }
		void rotate(Vec3f amount) { mRotationAmount += amount; }


	private:
		//Imported from Learning Modern 3D Graphics Programming. This is just temporary for now
		glm::mat4 RotateX(float fAngRad)
		{
			float fCos = cosf(fAngRad);
			float fSin = sinf(fAngRad);

			glm::mat4 theMat(1.0f);
			theMat[1].y = fCos; theMat[2].y = -fSin;
			theMat[1].z = fSin; theMat[2].z = fCos;
			return theMat;
		}

		glm::mat4 RotateY(float fAngRad)
		{
			float fCos = cosf(fAngRad);
			float fSin = sinf(fAngRad);

			glm::mat4 theMat(1.0f);
			theMat[0].x = fCos; theMat[2].x = fSin;
			theMat[0].z = -fSin; theMat[2].z = fCos;
			return theMat;
		}

		glm::mat4 RotateZ(float fAngRad)
		{
			float fCos = cosf(fAngRad);
			float fSin = sinf(fAngRad);

			glm::mat4 theMat(1.0f);
			theMat[0].x = fCos; theMat[1].x = -fSin;
			theMat[0].y = fSin; theMat[1].y = fCos;
			return theMat;
		}
	};
};

#endif

