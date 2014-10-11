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
		mHeightData = std::vector<float>(size*size, 0.4f);
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
		const int blockSize = 4;
		int mapSize = ceil(double(mSize-1) / double(blockSize));
		int mapSizeVertex = mapSize*blockSize + 1;

		GLuint indexData[blockSize+1][(blockSize+1)*2 + 1];
		mIndexData.clear();
		mIndexData.reserve((blockSize+1) * ((blockSize+1)*2 + 1));

		for (int y=0; y<blockSize+1; y++)
		{
			int offset = y*mapSizeVertex;

			for (int x=0; x<blockSize+1; x++)
			{
				mIndexData.push_back(x+offset);
				mIndexData.push_back(x+mapSizeVertex + offset);
			}

			mIndexData.push_back(PRIMITIVE_RESTART_INDEX);
		}

		std::cout << "Finished generating index data" << std::endl;
	}
};