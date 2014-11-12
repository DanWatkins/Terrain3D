//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _WORLD_TERRAIN_GENERATOR_H
#define _WORLD_TERRAIN_GENERATOR_H

#include <Main.h>
#include <World/Terrain/Data.h>

namespace t3d { namespace World { namespace Terrain { namespace Generator
{
    class Generator
	{
	public:
		virtual void generate(Data &terrainData, int size, int numberOfPasses, int seed) = 0;
	};
}}}}

#endif

