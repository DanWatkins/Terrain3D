//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Terrain_Renderer_H
#define _t3d_World_Terrain_Renderer_H

#include <Library.h>
#include <Core/ShaderProgram.h>
#include <World/Terrain/Data.h>
#include <World/Terrain/Water/Renderer.h>

namespace t3d { namespace world { namespace terrain
{
	enum class Mode
	{
		Normal,
		WireFrame
	};


	class Renderer : public core::ShaderProgram
	{
		Q_OBJECT

	public:
		Renderer() {}

		void init(Data *terrainData);
		void refreshIfNeeded();
		void prepareForRendering();

		void cleanup();
		void render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);
		void reloadShaders();

		void setLodFactor(float lodFactor) { mLodFactor = lodFactor; }
		void setIvdFactor(float ivdFactor) { mIvdFactor = ivdFactor; }
		void setMode(Mode mode) { mMode = mode; }
		Mode getMode() { return mMode; }

	protected:
		void addShaders() override;
		void queryUniformLocations() override;

	private:
		Q_DISABLE_COPY(Renderer)

		Data *mTerrainData;
		water::Renderer mWaterRenderer;

		GLuint mVao;
		GLuint mVbo[2];

		float mLodFactor;
		float mIvdFactor;
		Mode mMode = Mode::Normal;

		struct
		{
			GLint mvMatrix;
			GLint projMatrix;

			GLint terrainSize;
			GLint chunkSize;
			GLint lod;
			GLint ivd;
			GLint cameraPos;
			GLint heightScale;
			GLint spanSize;

			GLint textureMapResolution;
			GLint heightMapSize;
		} mUniforms;

		struct
		{
			GLuint heightMap;
			GLuint lightMap;
			GLuint indicies;
			GLuint terrain;
		} mTextures;

		struct
		{
			bool heightMap = false;
			bool lightMap = false;
		} mInvalidations;

	private:
		void loadTextures();
		void uploadHeightMap();
		void uploadLightMap();
	};
}}}

#endif

