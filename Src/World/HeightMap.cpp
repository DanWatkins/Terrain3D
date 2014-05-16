//=======================================================================================================================|
// Created 2014.05.03 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "HeightMap.h"

namespace t3d
{
	void HeightMap::reserve(Uint size)
	{
		bool powerOfTwo = !(size == 0) && !(size & (size - 1));

		if (!powerOfTwo)
		{
			std::cout << "Error: cannot reserve non-power of two size for HeightMap. Size=" << size << std::endl;
			//return;
		}

		mSize = size;
		mHeightData.clear();
		mHeightData = std::vector<Float>(size*size, 0.0f);
	}


	void HeightMap::set(Uint index, Float height)
	{
		mHeightData.at(index) = height;
	}


	void HeightMap::set(Uint indexX, Uint indexY, Float height)
	{
		Uint index = mSize*indexY + indexX;
		mHeightData.at(index) = height;
	}


	Uint8 HeightMap::get(Uint index)
	{
		return mHeightData.at(index);
	}


	Uint8 HeightMap::get(Uint indexX, Uint indexY)
	{
		return mHeightData.at(indexY*mSize + indexX);
	}


	void HeightMap::buildVertexData()
	{
		mVertexData.reserve(mSize*mSize*3);
		const Float spacing = 0.1f;
		std::vector<Float> colorVertexData;
		colorVertexData.reserve(mSize*mSize*3);

		std::cout << "\nBuilding Vertex Data" << std::endl;

		for (Uint y=0; y<mSize; y++)
		{
			for (Uint x = 0; x<mSize; x++)
			{
				mVertexData.push_back(spacing*(Float)x);
				mVertexData.push_back(mHeightData.at(y*mSize + x) / 255.0f);
				mVertexData.push_back(spacing*(Float)y);

				Float height = (Float)mHeightData.at(y*mSize + x);
				colorVertexData.push_back(height);
				colorVertexData.push_back(height);
				colorVertexData.push_back(height);
			}
		}

		//mVertexData.insert(mVertexData.end(), colorVertexData.begin(), colorVertexData.end());
	}


	std::vector<Float> *HeightMap::getVertexData()
	{
		return &mVertexData;
	}


	void HeightMap::buildIndexData()
	{
		Uint primitiveRestartCount = mSize - 2;
		Uint indexCount = (mSize * 2 - 2) * mSize + primitiveRestartCount;
		mIndexData.clear();
		mIndexData.reserve(indexCount);

		for (Uint y=0; y<mSize-1; y++)
		{
			Int indexStart = mSize*y;

			for (Uint x=0; x<mSize; x++)
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


	std::vector<Uint> *HeightMap::getIndexData()
	{
		return &mIndexData;
	}
};