//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "World.h"
#include <World/TerrainGenerator.h>
#include <stdio.h>

namespace t3d
{
	void World::init()
	{
		TerrainGenerator generator;
		generator.generate(mTerrainData, 65, 0, 123456); //(GLuint)time(NULL));

		return;
	}
}
