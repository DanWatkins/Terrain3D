//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAINDATA_H
#define _t3d_TERRAINDATA_H

#include <Main.h>
#include "Terrain/HeightMap.h"

namespace t3d
{
	class TerrainData
	{
	public:
		//TODO PURE HACKERY HERE
		HeightMap& heightMap() { return mHeightMap; }

		typedef std::vector<GLint> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }

	private:
		HeightMap mHeightMap;
		TextureIndicies mTextureIndicies;
	};
}


#endif
