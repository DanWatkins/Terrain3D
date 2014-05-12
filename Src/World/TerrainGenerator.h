//=======================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _TERRAIN_GENERATOR_H
#define _TERRAIN_GENERATOR_H

#include "HeightMap.h"

namespace t3d
{
	class TerrainGenerator
	{
	private:
		const Float mLowBound = 0.0f;
		const Float mHightBound = 255.0f;

		//std::vector<Float> mHeights;
		HeightMap mHeightMap;

		void init(Int size);
		void applyRandomFault(HeightMap &heightMap, Float faultAmount);

	public:
		HeightMap generate(Int size);	//TODO return a pointer or something LOL
	};
};

#endif

