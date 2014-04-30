//=======================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _t3d_HEIGHT_MAP_H
#define _t3d_HEIGHT_MAP_H

#include "../Main.h"
#include <vector>

namespace t3d
{
	class HeightMap
	{
	private:
		std::vector<Uint8> mHeightData;
		Uint mSize;

	public:
		HeightMap()
		{
			mSize = 64;
		}


		void reserve(Uint size)
		{
			bool powerOfTwo = !(size == 0) && !(size & (size - 1));

			if (!powerOfTwo)
				std::cout << "Error: cannot reserve non-power of two size for HeightMap. Size=" << size << std::endl;

			mSize = size;

			mHeightData = std::vector<Uint8>(size*size, 0);
		}


		void set(Uint index, Uint8 height) 
		{
			mHeightData.at(index) = height;
		}


		void set(Uint indexX, Uint indexY, Uint8 height)
		{
			Uint index = mSize*indexY + indexX;
			mHeightData.at(index) = height;
		}
	};
};


#endif

