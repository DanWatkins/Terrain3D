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
	World::World()
	{
	}


	void World::init(const WorldConfiguration &configuration)
	{
		Terrain::Generator::FaultFormation generator;
		mTerrainData.setTextureMapResolution(configuration.generatorTextureMapResolution);

		generator.generate(mTerrainData,
						   configuration.generatorSize,
						   280,
						   (configuration.generatorSeed == 0)
									? (int)time(NULL) : configuration.generatorSeed);
		{
			Terrain::Data::HeightIndex hi;
			hi[0.25f] = 0;
			hi[0.35f] = 1;
			hi[0.75f] = 2;
			hi[1.00f] = 3;
			mTerrainData.computeTextureIndicies(hi);
		}

		mTerrainData.lightMap().reserve(configuration.generatorSize);
		Terrain::Lighting::Slope::computeBrightness(mTerrainData.lightMap(),
													mTerrainData.heightMap());
	}
}}
