//=======================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "TerrainGenerator.h"

namespace t3d
{
	void TerrainGenerator::init(Int size)
	{
		//mHeights = std::vector<Float>(size*size, (mHightBound-mLowBound)/4.0f);
		mHeightMap.reserve(size);
	}
	

	void TerrainGenerator::applyRandomFault(HeightMap &heightMap, Float faultAmount)
	{
		//create the fault line from two random points
		Vec2f p1((Float)randInt(0, heightMap.getSize()), (Float)randInt(0, heightMap.getSize()));
		Vec2f p2((Float)randInt(0, heightMap.getSize()), (Float)randInt(0, heightMap.getSize()));
		Float slope = (p2.y-p1.y)/(p2.x-p1.x);
		Float yInt = p1.x*slope;

		Bool applyIfAbove = randBool();

		//go through every height and check whether it is on the side of @side
		//if it is, increase the height by @faultAmount
		for (Float y=0; y<(Float)heightMap.getSize(); y+=1.0f)
		{
			for (Float x=0; x<(Float)heightMap.getSize(); x+=1.0f)
			{
				Uint8 height = heightMap.get(x, y);
				Bool isAbove = y > (slope*x + yInt);
				Bool applyFault = (applyIfAbove == isAbove);

				if (applyFault)
					heightMap.set(x, y, height + (Uint8)faultAmount);
			}
		}
	}


	HeightMap TerrainGenerator::generate(Int size)
	{
		init(size);

		const Int numberOfPasses = 10;

		for (Int i=0; i<numberOfPasses; i++)
		{
			applyRandomFault(mHeightMap, 100/(i+1));
		}

		return mHeightMap;
	}
};