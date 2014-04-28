//=======================================================================================================================|
// Created 2014.04.27 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

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

	void MatrixStack::perspective(Float fovDeg, Float aspectRatio, Float zNear, Float zFar)
	{
		mCurrentMatrix *= glm::perspective(fovDeg, aspectRatio, zNear, zFar);
	}


	void MatrixStack::orthographic(Float left, Float right, Float bottom, Float top, Float zNear = 1.0f, Float zFar = 1.0f)
	{
		mCurrentMatrix *=  glm::ortho(left, right, bottom, top, zNear, zFar);
	}


	void MatrixStack::pixelPerfectOrtho(glm::ivec2 size, Vec2f depthRange, Bool isTopLeft = true)
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