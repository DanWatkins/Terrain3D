//=======================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Camera.h"
#include "../Core/MatrixStack.h"

namespace t3d
{
	Camera::Camera() :
		mPosition(0, 0, 1),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(0.01f),
		mFarPlane(100.0f),
		mAspectRatio(16/9)
	{
	}


	void Camera::uploadTerrainData(HeightMap &heightMap)
	{
		glGenVertexArrays(1, &mRenderData.vao_terrain);
		glBindVertexArray(mRenderData.vao_terrain);

		//vertex data
		Uint vbo;
		heightMap.buildVertexData();
		std::vector<Float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Float)*terrainVertexData->size(), &(*terrainVertexData)[0], GL_STATIC_DRAW);


		//index data
		Uint ibo;
		heightMap.buildIndexData();
		std::vector<Uint16> *terrainIndexData = heightMap.getIndexData();
		mRenderData.indexCount = terrainIndexData->size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Uint16)*terrainIndexData->size(), &(*terrainIndexData)[0], GL_STATIC_DRAW);

		int size = sizeof(Uint16)*terrainIndexData->size();

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(HeightMap::PRIMITIVE_RESTART_INDEX);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);	//pos
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(terrainVertexData->size()*2));	//color

		//glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glBindVertexArray(0);
	}
	

	void Camera::init(Uint program, World *world)
	{
		mWorld = world;

		glUseProgram(program);
		mRenderData.program = program;

		mRenderData.uloc_cameraMatrix = glGetUniformLocation(program, "cameraMatrix");		
		mRenderData.uloc_modelMatrix = glGetUniformLocation(program, "modelMatrix");

		uploadTerrainData(world->getHeightMap());

		glUseProgram(0);
	}



	void Camera::render()
	{
		glUseProgram(mRenderData.program);


		glUniformMatrix4fv(mRenderData.uloc_cameraMatrix, 1, GL_FALSE, glm::value_ptr(getTotalMatrix()));
		glUniformMatrix4fv(mRenderData.uloc_modelMatrix, 1, GL_FALSE, glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

		glBindVertexArray(mRenderData.vao_terrain);
		glDrawElements(GL_TRIANGLE_STRIP, mRenderData.indexCount, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}


	Mat4 Camera::getOrientation()
	{
		Mat4 orientation;
		orientation = glm::rotate(orientation, mVerticalAngle, Vec3f(1, 0, 0));
		orientation = glm::rotate(orientation, mHorizontalAngle, Vec3f(0, 1, 0));
		return orientation;
	}


	void Camera::lookAt(Vec3f position)
	{
		if (position == mPosition)
		{
			std::cout << "MEGA ERROR: You are trying to look at your origin" << std::endl;
			return;
		}

		Vec3f direction = glm::normalize(position - mPosition);
		mVerticalAngle = radToDeg(asinf(-direction.y));
		mHorizontalAngle = -radToDeg(atan2f(-direction.x, -direction.z));
		normalizeAngles();
	}


	Vec3f Camera::getForward()
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 0, -1, 1));
	}


	Vec3f Camera::getRight()
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(1, 0, 0, 1));
	}


	Vec3f Camera::getUp()
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 1, 0, 1));
	}


	Mat4 Camera::getTotalMatrix()
	{
		return getPerspectiveMatrix() * getViewMatrix();
	}


	Mat4 Camera::getPerspectiveMatrix()
	{
		return glm::perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
	}


	Mat4 Camera::getViewMatrix()
	{
		return getOrientation() * glm::translate(Mat4(), -mPosition);
	}


	void Camera::normalizeAngles()
	{
		mHorizontalAngle = fmodf(mHorizontalAngle, 360.0f);
		if (mHorizontalAngle < 0.0f)
			mHorizontalAngle += 360.0f;

		if (mVerticalAngle > mMaxVerticalAngle)
			mVerticalAngle = mMaxVerticalAngle;
		else if (mVerticalAngle < -mMaxVerticalAngle)
			mVerticalAngle = -mMaxVerticalAngle;
	}
};