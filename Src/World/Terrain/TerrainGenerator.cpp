//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/TerrainGenerator.h>

namespace t3d
{
	TerrainGenerator::TerrainGenerator() :
		mLowBound(0.0f),
		mHightBound(255.0f)
	{
	}


	void TerrainGenerator::init(int size)
	{
		mTerrainData->heightMap().reserve(size);
	}
	

	void TerrainGenerator::applyRandomFault(float faultAmount)
	{
		//create the fault line from two random points
		Vec2f p1((float)randInt(0, mTerrainData->heightMap().getSize()), (float)randInt(0, mTerrainData->heightMap().getSize()));
		Vec2f p2;

		do
		{
			p2 = Vec2f((float)randInt(0, mTerrainData->heightMap().getSize()), (float)randInt(0, mTerrainData->heightMap().getSize()));
		} while (p2 == p1);

		
		float dirX1 = p2.x-p1.x;
		float dirY1 = p2.y - p1.y;
		int size = mTerrainData->heightMap().getSize();

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
			{
				float dirX2 = x - p1.x;
				float dirY2 = y - p1.y;

				if ((dirX2*dirY1 - dirX1*dirY2) > 0)
					mTerrainData->heightMap().set(x, y, mTerrainData->heightMap().get((GLuint)x, (GLuint)y) + faultAmount);
			}
		}
	}


	void TerrainGenerator::normalizeHeights()
	{
		float min = mTerrainData->heightMap().get(0);
		float max = mTerrainData->heightMap().get(0);
		int size = mTerrainData->heightMap().getSize();

		for (int i=1; i<size*size; i++)
		{
			if (mTerrainData->heightMap().get(i) > max)
				max = mTerrainData->heightMap().get(i);
			else if (mTerrainData->heightMap().get(i) < min)
				min = mTerrainData->heightMap().get(i);
		}


		if (max <= min)
			return;

		float height = max-min;

		for (int i=0; i<size*size; i++)
		{
			mTerrainData->heightMap().set(i, (mTerrainData->heightMap().get(i)-min) / height * 255.0f);
		}
	}


	void TerrainGenerator::smoothHeightBand(GLuint index, int stride, GLuint length, float intensity)
	{
		float v = mTerrainData->heightMap().get(index);
		int j = stride; 
		
		for (GLuint i=0; i<length-1; i++)
		{
			float height = (float)mTerrainData->heightMap().get(j+index);
			mTerrainData->heightMap().set(j+index, intensity*v + (1-intensity) * height);

			v = (float)mTerrainData->heightMap().get(j + index);
			j += stride;
		}
	}


	void TerrainGenerator::smoothHeight(float intensity)
	{
		int size = mTerrainData->heightMap().getSize();

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


	void TerrainGenerator::generate(TerrainData &terrainData, int size, int numberOfPasses, int seed)
	{
		mTerrainData = &terrainData;
		init(size);
		std::srand(seed);

		for (int i=0; i<numberOfPasses; i++)
		{
			const float maxDelta = 255.0f;
			const float minDelta = 0.0f;
			float amount = maxDelta - ((maxDelta - minDelta) * i) / size;
			amount += 15.0f;

			applyRandomFault(amount);
		}

		smoothHeight(0.55f);
		normalizeHeights();
	}
}
