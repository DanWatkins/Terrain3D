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

		HeightMap& heightMap() { return mHeightMap; }
		LightMap &lightMap() { return mLightMap; }

		typedef QMap<float, GLubyte> HeightIndex;
		void computeTextureIndicies(const HeightIndex &heightIndex);

		typedef QVector<GLubyte> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }

		void setTextureMapResolution(int resolution) { mTextureMapResolution = resolution; }
		int textureMapResolution() const { return mTextureMapResolution; }
		void setHeightScale(float heightScale) { mHeightScale = heightScale; }
		float heightScale() const { return mHeightScale; }
		void setSpanSize(int spanSize) { mSpanSize = spanSize; }
		int spanSize() const { return mSpanSize; }
		void setChunkSize(int chunkSize) { mChunkSize = chunkSize; }
		int chunkSize() const { return mChunkSize; }

	private:
		HeightMap mHeightMap;
		LightMap mLightMap;
		TextureIndicies mTextureIndicies;

		int mTextureMapResolution;
		float mHeightScale;
		int mSpanSize;
		int mChunkSize;
	};
}}}

#endif
