//==================================================================================================================|
// Created 2015.03.08 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_world_terrain_water_Renderer_H
#define _t3d_world_terrain_water_Renderer_H

#include <Library.h>
#include <Core/ShaderProgram.h>
#include <World/Terrain/Data.h>

#include <ValpineBase/Loadable.h>

namespace t3d { namespace world { namespace terrain { namespace water
{
    class Renderer : public core::ShaderProgram, public vbase::Loadable
	{
	public:
		Renderer() {}
		~Renderer() {}

		void init(Data *terrainData);
		void refresh();

		void cleanup();
        void render(const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);

        vbase::Property<float> pWaterLevel = 0.3f;

	protected:
		void addShaders() override;
		void queryUniformLocations() override;
		void refreshUniformValues() override;

	private:
		Q_DISABLE_COPY(Renderer)

		GLuint mVao;

		struct
		{
			GLint mvMatrix;
			GLint projMatrix;
			GLint size;
			GLint spanSize;
			GLint heightScale;
			GLint waterLevel;
			GLint timeDelta;
		} mUniforms;

		struct
		{
			GLuint water;
		} mTextures;

		struct
		{
			bool terrainData = false;
		} mInvalidations;

		Data *mTerrainData;
		QElapsedTimer mElapsedTimer;

	private:
		void loadShader(const QString &filename, QOpenGLShader::ShaderType shaderType);
		void loadShaders();
		void loadTextures();
	};
}}}}

#endif

