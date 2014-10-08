//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "World.h"
#include "HeightMap.h"
#include "TerrainGenerator.h"
#include <stdio.h>

namespace t3d
{
	void World::init()
	{
		TerrainGenerator generator;
		mHeightMap = generator.generate(128, 32, (GLuint)time(NULL));

		double r = fmod(50.0, 11.0);


		//std::cout << "Generated terrain data in " << clock.getElapsedTime().asSeconds() << " seconds" << std::endl;
		return;
	}
};