//=======================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "World.h"
#include "HeightMap.h"
#include "TerrainGenerator.h"
#include <stdio.h>

namespace t3d
{
	void World::init()
	{
		sf::Clock clock;

		/*
		const int mapSize = 512;
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
		*/

		TerrainGenerator generator;
		mHeightMap = generator.generate(128, (Uint)time(NULL));

		std::cout << "Generated terrain data in " << clock.getElapsedTime().asSeconds() << " seconds" << std::endl;
		return;
	}
};