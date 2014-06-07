//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Camera.h"
#include "../Core/MatrixStack.h"

namespace t3d
{
	Camera::Camera() :
		mPosition(0, 0, 0),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(0.01f),
		mFarPlane(600.0f),
		mAspectRatio(16/9)
	{
		lookAt(Vec3f(1, 0, 1));
	}


	void Camera::loadShaders()
	{
		GLuint shaders[2];
		shaders[0] = Shader::loadShader(String(gDefaultPathShaders) + "camera-vert.glsl", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(String(gDefaultPathShaders) + "camera-frag.glsl", GL_FRAGMENT_SHADER);

		mRenderData.program = Shader::linkFromShaders(shaders, 2);
	}


	void Camera::uploadTerrainData(HeightMap &heightMap)
	{
		sf::Clock clock;

		glGenVertexArrays(1, &mRenderData.vao_terrain);
		glBindVertexArray(mRenderData.vao_terrain);

		//vertex data
		GLuint vbo;
		heightMap.buildVertexData();
		const std::vector<float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint size = sizeof(float)*terrainVertexData->size();
		glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);

		//index data
		GLuint ibo;
		heightMap.buildIndexData();
		const std::vector<GLuint> *terrainIndexData = heightMap.getIndexData();
		mRenderData.indexCount = terrainIndexData->size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						sizeof(GLuint)*terrainIndexData->size(),
						&(*terrainIndexData)[0], GL_STATIC_DRAW);


		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(HeightMap::PRIMITIVE_RESTART_INDEX);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);	//pos

		int colorOffset = (terrainVertexData->size() / 2 * sizeof(float));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)colorOffset);	//color

		//glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glBindVertexArray(0);

		std::cout << "Processed and uploaded terrain data in "
					<< clock.getElapsedTime().asSeconds()
					<< " seconds"
					<< std::endl;
	}
	

	void Camera::init(World *world)
	{
		mWorld = world;

		loadShaders();
		glUseProgram(mRenderData.program);

		mRenderData.uloc_cameraMatrix = glGetUniformLocation(mRenderData.program, "cameraMatrix");		
		mRenderData.uloc_modelMatrix = glGetUniformLocation(mRenderData.program, "modelMatrix");

		uploadTerrainData(world->getHeightMap());

		glUseProgram(0);
	}



	void Camera::render()
	{
		glUseProgram(mRenderData.program);

		glUniformMatrix4fv(mRenderData.uloc_cameraMatrix, 1, GL_FALSE, glm::value_ptr(getTotalMatrix()));
		glUniformMatrix4fv(mRenderData.uloc_modelMatrix, 1, GL_FALSE,
							glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

		glBindVertexArray(mRenderData.vao_terrain);
		glDrawElements(GL_TRIANGLE_STRIP, mRenderData.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(0);
	}


	Mat4 Camera::getOrientation() const
	{
		Mat4 orientation;
		orientation = glm::rotate(orientation, mVerticalAngle, Vec3f(1, 0, 0));
		orientation = glm::rotate(orientation, mHorizontalAngle, Vec3f(0, 1, 0));
		return orientation;
	}


	void Camera::incOrientation(float rightAngle, float upAngle)
	{
		mHorizontalAngle += rightAngle;
		mVerticalAngle += upAngle;
		normalizeAngles();
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


	Vec3f Camera::getForward() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 0, -1, 1));
	}


	Vec3f Camera::getRight() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(1, 0, 0, 1));
	}


	Vec3f Camera::getUp() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 1, 0, 1));
	}


	Mat4 Camera::getTotalMatrix() const
	{
		return getPerspectiveMatrix() * getViewMatrix();
	}


	Mat4 Camera::getPerspectiveMatrix() const
	{
		return glm::perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
	}


	Mat4 Camera::getViewMatrix() const
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