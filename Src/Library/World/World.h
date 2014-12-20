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
	/**
	 * Contains all the configuration/settings relevant to a World
	 * instance. TODO this is actually redundant since all these settings are
	 * declared here as well as in the Application settings class. This is just
	 * a simple pass object for now and can probably be refactored out eventually.
	 */
	struct WorldConfiguration
	{
		int generatorSize;
		int generatorTextureMapResolution;
		int generatorSeed;
	};


	class World
	{
	private:
		Terrain::Data mTerrainData;

	public:
		World();
		void init(const WorldConfiguration &configuration);

		Terrain::Data& terrainData() { return mTerrainData; }
	};
}}

#endif

