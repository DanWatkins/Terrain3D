//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_HEIGHT_MAP_H
#define _t3d_HEIGHT_MAP_H

#include <Terrain3D/Library.h>

namespace t3d { namespace world { namespace terrain
{
	class HeightMap
	{
	private:
		QVector<float> mHeightData;
		int mSize = 0;

	public:
		void reserve(int size);
		void set(int index, float height);
		void set(int indexX, int indexY, float height);
		float get(int index) const;
		float get(int indexX, int indexY) const;

		const float* raw() const;
		int size() const { return mSize; }
	};
}}}


#endif

