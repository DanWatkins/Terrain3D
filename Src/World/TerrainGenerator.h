//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _TERRAIN_GENERATOR_H
#define _TERRAIN_GENERATOR_H

#include "HeightMap.h"

namespace t3d
{
	class TerrainGenerator
	{
	private:
		const float mLowBound = 0.0f;
		const float mHightBound = 255.0f;

		//std::vector<float> mHeights;
		HeightMap mHeightMap;

		void init(int size);
		void applyRandomFault(HeightMap &heightMap, float faultAmount);
		void normalizeHeights();
		void smoothHeightBand(GLuint indexStart, int stride, GLuint length, float intensity);
		void smoothHeight(float intensity);

	public:
		HeightMap generate(int size, int numberOfPasses, int seed);	//TODO return a pointer or something LOL
	};
};

#endif

