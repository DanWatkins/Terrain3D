//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAINDATA_H
#define _t3d_TERRAINDATA_H

#include <Main.h>
#include <World/Terrain/HeightMap.h>

namespace t3d { namespace World { namespace Terrain
{
	class Data
	{
	public:
		Data();

		//TODO PURE HACKERY HERE
		HeightMap& heightMap() { return mHeightMap; }

        void computeTextureIndicies();

		typedef std::vector<GLubyte> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }
		int textureMapResolution() { return mTextureMapResolution; }

	private:
		HeightMap mHeightMap;
		TextureIndicies mTextureIndicies;

		int mTextureMapResolution;
	};
}}}


#endif
