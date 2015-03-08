//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAINDATA_H
#define _t3d_TERRAINDATA_H

#include <Library.h>
#include <World/Terrain/HeightMap.h>
#include <World/Terrain/LightMap.h>

namespace t3d { namespace world { namespace terrain
{
	class Data
	{
	public:
		void cleanup() { /*nothing to cleanup*/ }

		//TODO PURE HACKERY HERE
		HeightMap& heightMap() { return mHeightMap; }
		LightMap &lightMap() { return mLightMap; }

		typedef QMap<float, GLubyte> HeightIndex;
		void computeTextureIndicies(const HeightIndex &heightIndex);

		typedef QVector<GLubyte> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }

		void setTextureMapResolution(int resolution) { mTextureMapResolution = resolution; }
		int textureMapResolution() { return mTextureMapResolution; }
		void setSpacing(float spacing) { mSpacing = spacing; }
		float spacing() { return mSpacing; }
		void setHeightScale(float heightScale) { mHeightScale = heightScale; }
		float heightScale() { return mHeightScale; }
		void setSpanSize(float spanSize) { mSpanSize = spanSize; }
		int spanSize() { return mSpanSize; }

	private:
		HeightMap mHeightMap;
		LightMap mLightMap;
		TextureIndicies mTextureIndicies;

		int mTextureMapResolution;
		float mSpacing;
		float mHeightScale;
		int mSpanSize;
	};
}}}

#endif
