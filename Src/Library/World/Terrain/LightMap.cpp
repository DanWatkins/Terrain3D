//==================================================================================================================|
// Created 2014.11.17 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "LightMap.h"

namespace t3d { namespace World { namespace Terrain
{
	LightMap::LightMap() :
		mSize(0)
	{

	}


	void LightMap::reserve(unsigned size)
	{
		mSize = size;
		mValues.reserve(mSize*mSize);
	}


	void LightMap::set(int x, int y, GLubyte value)
	{
		mValues[x + y*mSize] = value;
	}


	GLubyte LightMap::get(int x, int y)
	{
		return mValues[x + y*mSize];
	}
}}}
