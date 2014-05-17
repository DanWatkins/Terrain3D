//=======================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "TerrainGenerator.h"

namespace t3d
{
	void TerrainGenerator::init(Int size)
	{
		mHeightMap.reserve(size);
	}
	

	void TerrainGenerator::applyRandomFault(HeightMap &heightMap, Float faultAmount)
	{
		//create the fault line from two random points
		Vec2f p1((Float)randInt(0, heightMap.getSize()), (Float)randInt(0, heightMap.getSize()));
		Vec2f p2;

		do
		{
			p2 = Vec2f((Float)randInt(0, heightMap.getSize()), (Float)randInt(0, heightMap.getSize()));
		} while (p2 == p1);

		
		Float dirX1 = p2.x-p1.x;
		Float dirY1 = p2.y - p1.y;
		Int size = heightMap.getSize();

		for (Int y=0; y<size; y++)
		{
			for (Int x=0; x<size; x++)
			{
				Float dirX2 = x - p1.x;
				Float dirY2 = y - p1.y;

				if ((dirX2*dirY1 - dirX1*dirY2) > 0)
					heightMap.set(x, y, heightMap.get((Uint)x, (Uint)y) + faultAmount);
			}
		}
	}


	void TerrainGenerator::normalizeHeights()
	{
		Float min = mHeightMap.get(0);
		Float max = mHeightMap.get(0);
		Int size = mHeightMap.getSize();

		for (Int i=1; i<size*size; i++)
		{
			if (mHeightMap.get(i) > max)
				max = mHeightMap.get(i);
			else if (mHeightMap.get(i) < min)
				min = mHeightMap.get(i);
		}


		if (max <= min)
			return;

		Float height = max-min;

		for (Int i=0; i<size*size; i++)
		{
			mHeightMap.set(i, (mHeightMap.get(i)-min) / height * 255.0f);
		}
	}


	void TerrainGenerator::smoothHeightBand(Uint index, Int stride, Uint length, Float intensity)
	{
		Float v = mHeightMap.get(index);
		Int j = stride; 
		
		for (Uint i=0; i<length-1; i++)
		{
			Float height = (Float)mHeightMap.get(j+index);
			mHeightMap.set(j+index, intensity*v + (1-intensity) * height);

			v = (Float)mHeightMap.get(j + index);
			j += stride;
		}
	}


	void TerrainGenerator::smoothHeight(Float intensity)
	{
		Int size = mHeightMap.getSize();

		//left to right
		for (Int i = 0; i<size; i++)
			smoothHeightBand(size*i, 1, size, intensity);

		//right to left
		for (Int i = 0; i<size; i++)
			smoothHeightBand(size*i + size-1, -1, size, intensity);

		//top to bottom
		for (Int i = 0; i<size; i++)
			smoothHeightBand(i, size, size, intensity);

		//bottom to top
		for (Int i = 0; i<size; i++)
			smoothHeightBand(size*(size-1)+i, -size, size, intensity);
	}


	HeightMap TerrainGenerator::generate(Int size, Int seed)
	{
		init(size);
		std::srand(seed);

		const Float numberOfPasses = 256;
		const Float tweaker = 2.0f;

		for (Int i=0; i<numberOfPasses; i++)
		{
			const Float maxDelta = 255.0f;
			const Float minDelta = 0.0f;
			Float amount = maxDelta - ((maxDelta - minDelta) * i) / size;
			amount += 15.0f;

			applyRandomFault(mHeightMap, amount);

			std::cout << amount << std::endl;
		}

		smoothHeight(0.50f);
		normalizeHeights();

		return mHeightMap;
	}
};