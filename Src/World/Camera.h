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
			GLuint program;
			GLuint vao_terrain;
			GLuint indexCount;

			GLuint uloc_cameraMatrix;
			GLuint uloc_modelMatrix;
		} mRenderData;

		World *mWorld;

		Vec3f mPosition;
		float mHorizontalAngle, mVerticalAngle;
		float mFieldOfView;
		float mNearPlane, mFarPlane;
		float mAspectRatio;

		const float mMaxVerticalAngle = 85.0f;

	private:
		void loadShaders();
		void uploadTerrainData(HeightMap &heightMap);
		void normalizeAngles();


	public:
		Camera();

		void init(World *world);
		void render();

		void setPosition(Vec3f position) { mPosition = position; }
		void incPosition(Vec3f positionAmount) { mPosition += positionAmount; }
		Vec3f getPosition() const { return mPosition; }

		void setFieldOfView(float fieldOfView);
		float getFieldOfView() const { return mFieldOfView; }

		void setNearPlane(float nearPlane) { mNearPlane = nearPlane; }
		float getNearPlane() const { return mNearPlane; }
		void setFarPlane(float farPlane) { mFarPlane = farPlane; }
		float getFarPlane() const { return mFarPlane; }

		void incOrientation(float rightAngle, float upAngle);
		Mat4 getOrientation() const;
		void lookAt(Vec3f position);

		void setAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; }
		float getAspectRatio() { return mAspectRatio; }

		Vec3f getForward() const;
		Vec3f getRight() const;
		Vec3f getUp() const;

		Mat4 getTotalMatrix() const;
		Mat4 getPerspectiveMatrix() const;
		Mat4 getViewMatrix() const;
	};
};

#endif

