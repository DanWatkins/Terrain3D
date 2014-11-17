//==================================================================================================================|
// Created 2014.11.17 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_LIGHT_MAP_H
#define _t3d_LIGHT_MAP_H

#include <Main.h>
#include <vector>

namespace t3d { namespace World { namespace Terrain
{
	/*
	 * Stores 8-bit normalized unsigned integers indicating the brightness for a given
	 * vertex when rendering terrain.
	 */
	class LightMap
	{
	private:
		QVector<GLubyte> mValues;
		unsigned mSize;

	public:
		LightMap();

		void reserve(unsigned size);
		void set(int x, int y, GLubyte value);
		GLubyte get(int x, int y);

		unsigned size() const { return mSize; }

		QVector<GLubyte>* raw() { return &mValues; }
	};
}}}


#endif

