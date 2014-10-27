//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAIN_RENDERER_H
#define _t3d_TERRAIN_RENDERER_H

#include <Main.h>
#include <Core/OpenGLWindow.h>
#include <World/World.h>

namespace t3d
{
	enum class Mode
	{
		Normal,
		WireFrame
	};

	class TerrainRenderData;

	class TerrainRenderer : protected QOpenGLFunctions_4_3_Core
	{
	public:
		TerrainRenderer(OpenGLWindow *window, World *world);
		~TerrainRenderer() {}

		void init();
		void render(Vec3f cameraPos, Mat4 totalMatrix);

		void setMode(Mode mode) { mMode = mode; }
		Mode getMode() { return mMode; }

	private:
		std::shared_ptr<TerrainRenderData> mRenderData;

		World *mWorld;
		QOpenGLShaderProgram mProgram;
		QOpenGLVertexArrayObject mVao;
		GLuint mTexture;
		GLuint mTextureSand;

		Mode mMode;

		

	private:
		void loadShaders();
		void loadTextures();
		Vec2i cameraPosToBlockPosition(Vec3f cameraPos);
	};
};

#endif

