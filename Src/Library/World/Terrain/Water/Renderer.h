//==================================================================================================================|
// Created 2015.03.08 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_world_terrain_water_Renderer_H
#define _t3d_world_terrain_water_Renderer_H

#include <Library.h>
#include <World/Terrain/Data.h>

namespace t3d { namespace world { namespace terrain { namespace water
{
	class Renderer : protected OpenGLFunctions
	{
	public:
		Renderer() {}

		void init(Data *terrainData, float waterLevel);
		void cleanup();
		void render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);
		void reloadShaders();

	private:
		Q_DISABLE_COPY(Renderer)

		unique<QOpenGLShaderProgram> mProgram;

		struct
		{
			GLint mvMatrix;
			GLint projMatrix;
			GLint size;
			GLint spanSize;
			GLint waterLevel;
		} mUniforms;

		struct
		{
			GLuint water;
		} mTextures;

		Data *mTerrainData;
		float mWaterLevel;

	private:
		void loadShader(const QString &filename, QOpenGLShader::ShaderType shaderType);
		void loadShaders();
		void loadTextures();
	};
}}}}

#endif

