//==================================================================================================================|
// Created 2014.11.21 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_NORMAL_MAP_H
#define _t3d_NORMAL_MAP_H

#include <Terrain3D/Library.h>

namespace t3d { namespace world { namespace terrain
{
	class HeightMap;

	class NormalMap
	{
	public:
		void generate(const HeightMap &hm);
		int size() { return mNormals.size(); }
		Vec3f get(int index) { return mNormals[index]; }

	private:
		QVector<Vec3f> mNormals;
	};
}}}


#endif

