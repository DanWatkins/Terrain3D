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
				Uint8 height = heightMap.get((Uint)x, (Uint)y);
				Bool isAbove = y > (slope*x + yInt);
				Bool applyFault = (applyIfAbove == isAbove);

				if (applyFault)
				{
					heightMap.set(x, y, height + (Uint8)faultAmount);
				}
			}
		}
	}


	void TerrainGenerator::smoothHeightBand(Uint index, Int stride, Uint length, Float intensity)
	{
		Float v = mHeightMap.get(index);
		Int j = stride; 
		
		for (Uint i=0; i<length-1; i++)
		{
			Float height = (Float)mHeightMap.get(j+index);
			mHeightMap.set(j+index, intensity*v + (1-intensity) * height);

			v = (Float)mHeightMap.get(j + index);
			j += stride;
		}
	}


	void TerrainGenerator::smoothHeight(Float intensity)
	{
		Uint size = mHeightMap.getSize();

		//left to right
		for (Uint i=0; i<size; i++)
			smoothHeightBand(size*i, 1, size, intensity);

		//right to left
		for (Uint i=0; i<size; i++)
			smoothHeightBand(size*i + size-1, -1, size, intensity);

		//top to bottom
		for (Uint i=0; i<size; i++)
			smoothHeightBand(i, size, size, intensity);

		//bottom to top
		for (Uint i=0; i<size; i++)
			smoothHeightBand(size*(size-1)+i, -size, size, intensity);
	}


	HeightMap TerrainGenerator::generate(Int size, Int seed)
	{
		init(size);
		std::srand(seed);

		const Int numberOfPasses = 192;
		const Int heightGainTweaker = 1;

		for (Int i=0; i<numberOfPasses; i++)
		{
			Float amount = ((mHightBound - mLowBound)*i) / (numberOfPasses / heightGainTweaker);
			applyRandomFault(mHeightMap, amount);
		}

		smoothHeight(0.60f);

		return mHeightMap;
	}
};