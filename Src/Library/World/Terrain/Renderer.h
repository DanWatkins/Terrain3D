//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAIN_RENDERER_H
#define _t3d_TERRAIN_RENDERER_H

#include <Library.h>
#include <World/Terrain/Data.h>
#include <World/Terrain/Water/Renderer.h>

namespace t3d { namespace world { namespace terrain
{
	enum class Mode
	{
		Normal,
		WireFrame
	};


	class Renderer : protected OpenGLFunctions
	{
	public:
		Renderer() {}

		void init(Data *terrainData);
		void prepareForRendering();

		void cleanup();
		void render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);
		void reloadShaders();

		void setLodFactor(float lodFactor) { mLodFactor = lodFactor; }
		void setIvdFactor(float ivdFactor) { mIvdFactor = ivdFactor; }
		void setMode(Mode mode) { mMode = mode; }
		Mode getMode() { return mMode; }

		void requestUniformReload() { mNeedsToReloadUniforms = true; }

	private:
		Q_DISABLE_COPY(Renderer)

		Data *mTerrainData;
		water::Renderer mWaterRenderer;
		unique<QOpenGLShaderProgram> mProgram;
		GLuint mVao;
		GLuint mVbo[2];

		float mLodFactor;
		float mIvdFactor;
		Mode mMode = Mode::Normal;
		bool mNeedsToReloadUniforms = true;

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


	private:
		void loadShader(const QString &filename, QOpenGLShader::ShaderType shaderType);
		void loadShaders();
		void loadTextures();

		void reloadUniforms();
		void uploadTerrainData();
	};
}}}

#endif

