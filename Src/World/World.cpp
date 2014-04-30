//=======================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "World.h"
#include "HeightMap.h"

namespace t3d
{
	void World::init()
	{
		const int mapSize = 64;
		HeightMap heightMap;
		heightMap.reserve(mapSize);
		
		for (int y=0; y<mapSize; y++)
		{
			for (int x=0; x<mapSize; x++)
			{
				heightMap.set(x, y, randInt(0, 255));
			}
		}

		return;
	}
};