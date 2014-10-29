//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "World.h"
#include <World/HeightMap.h>
#include <World/TerrainGenerator.h>
#include <stdio.h>

namespace t3d
{
	void World::init()
	{
		TerrainGenerator generator;
		mHeightMap = generator.generate(257, 80, 123456); //(GLuint)time(NULL));

		return;
	}
}
