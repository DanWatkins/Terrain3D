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

			Uint uloc_cameraMatrix;
			Uint uloc_modelMatrix;
		} mRenderData;

		World *mWorld;

		Vec3f mPosition;
		Float mHorizontalAngle, mVerticalAngle;
		Float mFieldOfView;
		Float mNearPlane, mFarPlane;
		Float mAspectRatio;

		const Float mMaxVerticalAngle = 85.0f;

	private:
		void uploadTerrainData(HeightMap &heightMap);
		void normalizeAngles();


	public:
		Camera();

		void init(Uint program, World *world);
		void render();

		void setPosition(Vec3f position) { mPosition = position; }
		void incPosition(Vec3f positionAmount) { mPosition += positionAmount; }
		Vec3f getPosition() { return mPosition; }

		void setFieldOfView(Float fieldOfView);
		Float getFieldOfView() { return mFieldOfView; }

		void setNearPlane(Float nearPlane) { mNearPlane = nearPlane; }
		Float getNearPlane() { return mNearPlane; }
		void setFarPlane(Float farPlane) { mFarPlane = farPlane; }
		Float getFarPlane() { return mFarPlane; }

		void offsetOrientation(Float upAngle, Float rightAngle);
		Mat4 getOrientation();
		void lookAt(Vec3f position);

		void setAspectRatio(Float aspectRatio) { mAspectRatio = aspectRatio; }
		Float getAspectRatio() { return mAspectRatio; }

		Vec3f getForward();
		Vec3f getRight();
		Vec3f getUp();

		Mat4 getTotalMatrix();
		Mat4 getPerspectiveMatrix();
		Mat4 getViewMatrix();
	};
};

#endif

