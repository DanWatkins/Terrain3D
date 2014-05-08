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
		const int mapSize = 16;
		mHeightMap.reserve(mapSize);
		Uint oldHeight = 128;
		Uint8 lastHeight = 128;
		
		for (int y=0; y<mapSize; y++)
		{
			for (int x=0; x<mapSize; x++)
			{
				Uint8 height = randInt(0, 255);
				mHeightMap.set(x, y, (height+lastHeight+oldHeight)/3);
				lastHeight = height;
				oldHeight = lastHeight;
			}
		}

		return;
	}
};