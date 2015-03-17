//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Camera.h"

namespace t3d { namespace world
{
	Camera::Camera() :
		mTerrainRenderer(),
		mPosition(-20, 0, -20),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(1.0f),
		mFarPlane(1500.0f),
		mAspectRatio(1), 
		mMaxVerticalAngle(95.0f)
	{
		lookAt(Vec3f(60, 20, 60));
	}


	void Camera::init()
	{
		initializeOpenGLFunctions();

		mTerrainRenderer.init(&mEnvironment->terrainData());

		mEntityRenderer.setManager(&mEnvironment->entityManager());
	}


	void Camera::refreshIfNeeded()
	{
		mTerrainRenderer.refreshIfNeeded();
	}


	void Camera::prepareForRendering()
	{
		mTerrainRenderer.prepareForRendering();
	}


	void Camera::cleanup()
	{
		mTerrainRenderer.cleanup();
	}


	void Camera::render()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);

		glClearColor(1.0f, 0.9f, 0.8f , 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		mTerrainRenderer.render(mPosition, viewMatrix(), perspectiveMatrix());
		
		mEntityRenderer.renderAll(totalMatrix());
		mEnvironment->assetManager().renderAllQueued();

		emit finishedRendering();
	}


	void Camera::resize(unsigned windowWidth, unsigned windowHeight)
	{
		mAspectRatio = (float)windowWidth / (float)windowHeight;
		glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	}


	void Camera::reloadShaders()
	{
		mTerrainRenderer.reloadShaders();
	}


	Mat4 Camera::orientaion() const
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


	Vec3f Camera::forward() const
	{
		return Vec3f(glm::inverse(orientaion()) * Vec4f(0, 0, -1, 1));
	}


	Vec3f Camera::right() const
	{
		return Vec3f(glm::inverse(orientaion()) * Vec4f(1, 0, 0, 1));
	}


	Vec3f Camera::up() const
	{
		return Vec3f(glm::inverse(orientaion()) * Vec4f(0, 1, 0, 1));
	}


	///// PRIVATE

	Mat4 Camera::totalMatrix() const
	{
		return perspectiveMatrix() * viewMatrix();
	}


	Mat4 Camera::perspectiveMatrix() const
	{
		return glm::perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
	}


	Mat4 Camera::viewMatrix() const
	{
		return orientaion() * glm::translate(Mat4(), -mPosition);
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
}}
