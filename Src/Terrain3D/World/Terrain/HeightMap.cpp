//==================================================================================================================|
// Created 2014.05.03 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "HeightMap.h"

namespace t3d::world::terrain {

void HeightMap::reserve(int size)
{
    mSize = size;
    mHeightData.clear();
    mHeightData = QVector<float>(size*size, 0.1f);
}

void HeightMap::set(int index, float height)
{
    mHeightData[index] = height;
}

void HeightMap::set(int indexX, int indexY, float height)
{
    int index = mSize*indexY + indexX;
    mHeightData[index] = height;
}

float HeightMap::get(int index) const
{
    return mHeightData.at(index);
}

float HeightMap::get(int indexX, int indexY) const
{
    return mHeightData.at(indexY*mSize + indexX);
}

const float* HeightMap::raw() const
{
    return mHeightData.isEmpty() ? nullptr : &mHeightData[0];
}

}
