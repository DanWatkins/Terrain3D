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


	class Renderer : public core::ShaderProgram, public IRefreshable
	{
		Q_OBJECT

	public:
		Renderer();
		~Renderer() {}

		void init(Data *terrainData);
		void refresh() override;
		void prepareForRendering();

		void cleanup();
		void render(const Vec3f &cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);
		void reloadShaders();

		Property<float> pLodFactor = 1.0f;
		Property<float> pIvdFactor = 100.0f;
		Property<Mode> pMode = Mode::Normal;

	protected:
		void addShaders() override;
		void queryUniformLocations() override;

	private:
		Q_DISABLE_COPY(Renderer)

		Data *mTerrainData;
		water::Renderer mWaterRenderer;

		GLuint mVao;
		GLuint mVbo[2];

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
			bool terrainData = false;
		} mInvalidations;

	private:
		void loadTextures();
		void uploadTerrainData();
	};
}}}

#endif

