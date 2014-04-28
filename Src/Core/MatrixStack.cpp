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
};