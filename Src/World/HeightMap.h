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

		std::vector<Float> mVertexData;
		std::vector<Int> mIndexData;

	public:
		static const Uint PRIMITIVE_RESTART_INDEX = (32*32)-1;
		
		HeightMap()
		{
			mSize = 64;
		}


		void reserve(Uint size);
		void set(Uint index, Uint8 height);
		void set(Uint indexX, Uint indexY, Uint8 height);

		void buildVertexData();
		Float *getVertexData();

		void buildIndexData();
		Int *getIndexData();
	};
};


#endif

