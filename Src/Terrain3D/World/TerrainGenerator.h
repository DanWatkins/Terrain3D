//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _TERRAIN_GENERATOR_H
#define _TERRAIN_GENERATOR_H

#include <Main.h>
#include <World/TerrainData.h>

namespace t3d
{
	class TerrainGenerator
	{
	private:
		float mLowBound;
		float mHightBound;
		TerrainData *mTerrainData;

		void init(int size);
		void computeTextureIndicies();

	public:
		TerrainGenerator();
		void generate(TerrainData &terrainData, int size, int numberOfPasses, int seed);
	};
};

#endif

