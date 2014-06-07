//==================================================================================================================|
// Created 2014.04.27 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "MatrixStack.h"

namespace t3d
{
	MatrixStack::MatrixStack()
		: mCurrentMatrix(1.0f)
	{
	}


	MatrixStack::MatrixStack(const Mat4 &initialMatrix)
		: mCurrentMatrix(initialMatrix)
	{
	}

	void MatrixStack::perspective(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		mCurrentMatrix *= glm::perspective(fovDeg, aspectRatio, zNear, zFar);
	}


	void MatrixStack::orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		mCurrentMatrix *=  glm::ortho(left, right, bottom, top, zNear, zFar);
	}


	void MatrixStack::pixelPerfectOrtho(const glm::ivec2 &size, const Vec2f &depthRange, bool isTopLeft)
	{
		if (isTopLeft)
		{
			translate(-1.0f, 1.0f, (depthRange.x + depthRange.y) / 2.0f);
			scale(2.0f / size.x, -2.0f / size.y, 1.0f);
		}
		else
		{
			translate(-1.0f, -1.0f, (depthRange.x + depthRange.y) / 2.0f);
			scale(2.0f / size.x, 2.0f / size.y, 2.0f / (depthRange.y - depthRange.x));
		}
	}
};