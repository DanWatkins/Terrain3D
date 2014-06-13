//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "TerrainGenerator.h"

namespace t3d
{
	void TerrainGenerator::init(int size)
	{
		mHeightMap.reserve(size);
	}
	

	void TerrainGenerator::applyRandomFault(HeightMap &heightMap, float faultAmount)
	{
		//create the fault line from two random points
		Vec2f p1((float)randInt(0, heightMap.getSize()), (float)randInt(0, heightMap.getSize()));
		Vec2f p2;

		do
		{
			p2 = Vec2f((float)randInt(0, heightMap.getSize()), (float)randInt(0, heightMap.getSize()));
		} while (p2 == p1);

		
		float dirX1 = p2.x-p1.x;
		float dirY1 = p2.y - p1.y;
		int size = heightMap.getSize();

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
			{
				float dirX2 = x - p1.x;
				float dirY2 = y - p1.y;

				if ((dirX2*dirY1 - dirX1*dirY2) > 0)
					heightMap.set(x, y, heightMap.get((GLuint)x, (GLuint)y) + faultAmount);
			}
		}
	}


	void TerrainGenerator::normalizeHeights()
	{
		float min = mHeightMap.get(0);
		float max = mHeightMap.get(0);
		int size = mHeightMap.getSize();

		for (int i=1; i<size*size; i++)
		{
			if (mHeightMap.get(i) > max)
				max = mHeightMap.get(i);
			else if (mHeightMap.get(i) < min)
				min = mHeightMap.get(i);
		}


		if (max <= min)
			return;

		float height = max-min;

		for (int i=0; i<size*size; i++)
		{
			mHeightMap.set(i, (mHeightMap.get(i)-min) / height * 255.0f);
		}
	}


	void TerrainGenerator::smoothHeightBand(GLuint index, int stride, GLuint length, float intensity)
	{
		float v = mHeightMap.get(index);
		int j = stride; 
		
		for (GLuint i=0; i<length-1; i++)
		{
			float height = (float)mHeightMap.get(j+index);
			mHeightMap.set(j+index, intensity*v + (1-intensity) * height);

			v = (float)mHeightMap.get(j + index);
			j += stride;
		}
	}


	void TerrainGenerator::smoothHeight(float intensity)
	{
		int size = mHeightMap.getSize();

		//left to right
		for (int i = 0; i<size; i++)
			smoothHeightBand(size*i, 1, size, intensity);

		//right to left
		for (int i = 0; i<size; i++)
			smoothHeightBand(size*i + size-1, -1, size, intensity);

		//top to bottom
		for (int i = 0; i<size; i++)
			smoothHeightBand(i, size, size, intensity);

		//bottom to top
		for (int i = 0; i<size; i++)
			smoothHeightBand(size*(size-1)+i, -size, size, intensity);
	}


	HeightMap TerrainGenerator::generate(int size, int numberOfPasses, int seed)
	{
		init(size);
		std::srand(seed);

		for (int i=0; i<numberOfPasses; i++)
		{
			const float maxDelta = 255.0f;
			const float minDelta = 0.0f;
			float amount = maxDelta - ((maxDelta - minDelta) * i) / size;
			amount += 15.0f;

			applyRandomFault(mHeightMap, amount);
		}

		smoothHeight(0.65f);
		normalizeHeights();

		return mHeightMap;
	}
};