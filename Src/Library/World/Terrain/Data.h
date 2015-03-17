//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Terrain_Data_H
#define _t3d_World_Terrain_Data_H

#include <Library.h>
#include <World/Terrain/HeightMap.h>
#include <World/Terrain/LightMap.h>

namespace t3d { namespace world { namespace terrain
{
	class Data : public QObject
	{
		Q_OBJECT

	public:
		void cleanup() { /*nothing to cleanup*/ }

		void resetHeightMap(HeightMap &heightMap) { mHeightMap = heightMap; emit heightMapChanged(); }	//TODO really need a move constructor there
		const HeightMap& heightMap() const { return mHeightMap; }
		void resetLightMap(LightMap &lightMap) { mLightMap = lightMap; emit lightMapChanged(); }
		const LightMap &lightMap() const { return mLightMap; }

		typedef QMap<float, GLubyte> HeightIndex;
		void computeTextureIndicies(const HeightIndex &heightIndex);

		typedef QVector<GLubyte> TextureIndicies;
		TextureIndicies& textureIndicies() { return mTextureIndicies; }

#define CHANGE_IF(param, member) if (param != member) { member = param;
		void setTextureMapResolution(int resolution) { CHANGE_IF(resolution, mTextureMapResolution) emit textureMapResolutionChanged(); } }
		int textureMapResolution() const { return mTextureMapResolution; }
		void setHeightScale(float heightScale) { CHANGE_IF(heightScale, mHeightScale) emit heightScaleChanged(); } }
		float heightScale() const { return mHeightScale; }
		void setSpanSize(int spanSize) { CHANGE_IF(spanSize, mSpanSize) emit spanSizeChanged(); } }
		int spanSize() const { return mSpanSize; }
		void setChunkSize(int chunkSize) { CHANGE_IF(chunkSize, mChunkSize) emit chunkSizeChanged(); } }
		int chunkSize() const { return mChunkSize; }
#undef CHANGE_IF

	signals:
		void heightMapChanged();
		void lightMapChanged();

		void textureMapResolutionChanged();
		void heightScaleChanged();
		void spanSizeChanged();
		void chunkSizeChanged();

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
