//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/TerrainGenerator.h>
#include "HeightMap.h"

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
	

	void applyRandomFault(HeightMap &heightMap, float faultAmount)
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


	void normalizeHeights(HeightMap &heightMap)
	{
		float min = heightMap.get(0);
		float max = heightMap.get(0);
		int size = heightMap.getSize();

		for (int i=1; i<size*size; i++)
		{
			if (heightMap.get(i) > max)
				max = heightMap.get(i);
			else if (heightMap.get(i) < min)
				min = heightMap.get(i);
		}


		if (max <= min)
			return;

		float height = max-min;

		for (int i=0; i<size*size; i++)
		{
			heightMap.set(i, (heightMap.get(i)-min) / height * 255.0f);
		}
	}


	void smoothHeightBand(HeightMap &heightMap, GLuint index, int stride, GLuint length, float intensity)
	{
		float v = heightMap.get(index);
		int j = stride; 
		
		for (GLuint i=0; i<length-1; i++)
		{
			float height = (float)heightMap.get(j+index);
			heightMap.set(j+index, intensity*v + (1-intensity) * height);

			v = (float)heightMap.get(j + index);
			j += stride;
		}
	}


	void smoothHeight(HeightMap &heightMap, float intensity)
	{
		int size = heightMap.getSize();

		//left to right
		for (int i = 0; i<size; i++)
			smoothHeightBand(heightMap, size*i, 1, size, intensity);

		//right to left
		for (int i = 0; i<size; i++)
			smoothHeightBand(heightMap, size*i + size-1, -1, size, intensity);

		//top to bottom
		for (int i = 0; i<size; i++)
			smoothHeightBand(heightMap, i, size, size, intensity);

		//bottom to top
		for (int i = 0; i<size; i++)
			smoothHeightBand(heightMap, size*(size-1)+i, -size, size, intensity);
	}


	void TerrainGenerator::computeTextureIndicies()
	{
		int size = mTerrainData->heightMap().getSize();
		mTerrainData->textureIndicies().resize(size*size);

		for (int y=0; y<size; ++y)
		{
			for (int x=0; x<size; ++x)
			{
				float height = mTerrainData->heightMap().get(x + y*size) / 255.0f;
				int index = 0;

				//which texture should we use?
				if (height > 0.8f) //mountain
					index = 3;
				else if (height > 0.4f) //grass
					index = 2;
				else if (height > 0.2f) //sand
					index = 1;
				else                    //water
					index = 0;

				mTerrainData->textureIndicies()[x + y*size] = index;
			}
		}
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

			applyRandomFault(mTerrainData->heightMap(), amount);
		}

		smoothHeight(mTerrainData->heightMap(), 0.55f);
		normalizeHeights(mTerrainData->heightMap());
		computeTextureIndicies();
	}
}
