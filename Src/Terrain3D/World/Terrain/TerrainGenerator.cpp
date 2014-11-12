//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/TerrainGenerator.h>
#include <World/Terrain/Generator/FaultFormation.h>
#include "HeightMap.h"

namespace t3d
{
	TerrainGenerator::TerrainGenerator() :
		mLowBound(0.0f),
		mHightBound(255.0f)
	{
	}


	void TerrainGenerator::generate(TerrainData &terrainData, int size, int numberOfPasses, int seed)
	{
		mTerrainData = &terrainData;

        FaultFormation::generate(terrainData.heightMap(), size, numberOfPasses, seed);
        mTerrainData->computeTextureIndicies();
	}
}
