//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_WORLD_H
#define _t3d_WORLD_H

#include <World/Terrain/Data.h>

namespace t3d { namespace World
{
	class World
	{
	private:
		Terrain::Data mTerrainData;

	public:
		struct Configuration
		{
			int generatorSize;
			int generatorTextureMapResolution;
			int generatorSeed;
		};

	public:
		World();
		void init(const Configuration &configuration);

		Terrain::Data& terrainData() { return mTerrainData; }
	};
}}

#endif

