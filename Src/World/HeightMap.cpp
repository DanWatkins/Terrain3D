//==================================================================================================================|
// Created 2014.05.03 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "HeightMap.h"

namespace t3d
{
	void HeightMap::reserve(GLuint size)
	{
		bool powerOfTwo = !(size == 0) && !(size & (size - 1));

		if (!powerOfTwo)
		{
			std::cout << "Error: cannot reserve non-power of two size for HeightMap. Size=" << size << std::endl;
			//return;
		}

		mSize = size;
		mHeightData.clear();
		mHeightData = std::vector<float>(size*size, 0.0f);
	}


	void HeightMap::set(GLuint index, float height)
	{
		mHeightData.at(index) = height;
	}


	void HeightMap::set(GLuint indexX, GLuint indexY, float height)
	{
		GLuint index = mSize*indexY + indexX;
		mHeightData.at(index) = height;
	}


	float HeightMap::get(GLuint index) const
	{
		return mHeightData.at(index);
	}


	float HeightMap::get(GLuint indexX, GLuint indexY) const
	{
		return mHeightData.at(indexY*mSize + indexX);
	}


	void HeightMap::buildVertexData(float spacing)
	{
		mVertexData.reserve(mSize*mSize*3);

		std::cout << "\nBuilding Vertex Data" << std::endl;

		for (GLuint y=0; y<mSize; y++)
		{
			for (GLuint x = 0; x<mSize; x++)
			{
				mVertexData.push_back(spacing*(float)x);
				float height = mHeightData.at(y*mSize + x) / 255.0f;
				mVertexData.push_back(height);
				mVertexData.push_back(spacing*(float)y);
			}
		}
	}


	void HeightMap::buildIndexData()
	{
		GLuint primitiveRestartCount = mSize - 2;
		GLuint indexCount = (mSize * 2 - 2) * mSize + primitiveRestartCount;
		mIndexData.clear();
		mIndexData.reserve(indexCount);

		for (GLuint y=0; y<mSize-1; y++)
		{
			int indexStart = mSize*y;

			for (GLuint x=0; x<mSize; x++)
			{
				mIndexData.push_back(indexStart+x);
				mIndexData.push_back(indexStart+x+mSize);
			}

			if (y < mSize-2)
			{
				mIndexData.push_back(PRIMITIVE_RESTART_INDEX);
			}
		}
	}
};