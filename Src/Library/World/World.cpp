//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "World.h"
#include <World/Terrain/Generator/FaultFormation.h>
#include <World/Terrain/Lighting/Slope.h>
#include <stdio.h>

namespace t3d { namespace World
{
	World::World() :
		mTerrainData(4)
	{
	}


	void World::init()
	{
		Terrain::Generator::FaultFormation generator;
		generator.generate(mTerrainData, 129, 60, 123456); //(GLuint)time(NULL));
		{
			Terrain::Data::HeightIndex hi;
			hi[0.25f] = 0;
			hi[0.35f] = 1;
			hi[0.80f] = 2;
			hi[1.00f] = 3;
			mTerrainData.computeTextureIndicies(hi);
		}

		Terrain::Lighting::Slope::computeBrightness(mTerrainData.lightMap(),
													mTerrainData.heightMap());
	}
}}
