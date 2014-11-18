//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_HEIGHT_MAP_H
#define _t3d_HEIGHT_MAP_H

#include <Main.h>
#include <vector>

namespace t3d { namespace World { namespace Terrain
{
	class HeightMap
	{
	private:
		QVector<float> mHeightData;
		uint mSize;

		QVector<float> mVertexData;

	public:
		HeightMap()
		{
			mSize = 0;
		}


		void reserve(int size);
		void set(int index, float height);
		void set(int indexX, int indexY, float height);
		float get(int index) const;
		float get(int indexX, int indexY) const;

		void buildVertexData(float spacing);
		const QVector<float> *getVertexData() const { return &mVertexData; }

		uint size() const { return mSize; }
	};
}}}


#endif

