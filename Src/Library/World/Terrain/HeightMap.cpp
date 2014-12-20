//==================================================================================================================|
// Created 2014.05.03 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "HeightMap.h"

namespace t3d { namespace World { namespace Terrain
{
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


	void HeightMap::buildVertexData(float spacing)
	{
		mVertexData.reserve(mSize*mSize*3);

		qDebug() << "Building Vertex Data";

		for (int y=0; y<mSize; y++)
		{
			for (int x = 0; x<mSize; x++)
			{
				mVertexData.push_back(spacing*(float)x);
				float height = mHeightData.at(y*mSize + x);
				mVertexData.push_back(height);
				mVertexData.push_back(spacing*(float)y);
			}
		}
	}
}}}
