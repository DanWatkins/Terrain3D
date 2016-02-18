//==================================================================================================================|
// Created 2014.11.17 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "LightMap.h"

namespace t3d { namespace world { namespace terrain {
LightMap::LightMap() :
	mSize(0)
{

}


void LightMap::reserve(int size)
{
	mSize = size;
	mValues = ValueVector(size*size, std::numeric_limits<ValueType>::max());
}


void LightMap::set(int x, int y, float value)
{
	mValues[x + y*mSize] = ValueType(value * static_cast<float>(std::numeric_limits<ValueType>::max()));
}


float LightMap::get(int x, int y)
{
	return static_cast<float>(mValues[x + y*mSize]) / static_cast<float>(std::numeric_limits<ValueType>::max());
}

}}}
