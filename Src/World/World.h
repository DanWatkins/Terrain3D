//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_WORLD_H
#define _t3d_WORLD_H

#include <World/TerrainData.h>

namespace t3d
{
	class World
	{
	private:
		TerrainData mTerrainData;

	public:
		void init();

		TerrainData& terrainData() { return mTerrainData; }
	};
};

#endif

