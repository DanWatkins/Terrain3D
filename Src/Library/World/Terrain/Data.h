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
#include <World/Terrain/LightMap.h>

namespace t3d { namespace World { namespace Terrain
{
	class Data
	{
	public:
		void cleanup() { /*nothing to cleanup*/ }

		//TODO PURE HACKERY HERE
		HeightMap& heightMap() { return mHeightMap; }
		LightMap &lightMap() { return mLightMap; }

		typedef QMap<float, int> HeightIndex;
		void computeTextureIndicies(const HeightIndex &heightIndex);

		typedef QVector<GLubyte> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }

		void setTextureMapResolution(int resolution) { mTextureMapResolution = resolution; }
		int textureMapResolution() { return mTextureMapResolution; }

	private:
		HeightMap mHeightMap;
		LightMap mLightMap;
		TextureIndicies mTextureIndicies;

		int mTextureMapResolution;
	};
}}}

#endif
