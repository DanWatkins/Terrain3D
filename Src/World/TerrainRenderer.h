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

	class TerrainRenderer : protected QOpenGLFunctions_4_3_Core
	{
	public:
		TerrainRenderer(OpenGLWindow *window, World *world);

		void init();
		void render(Vec3f cameraPos, Mat4 totalMatrix);

		void setMode(Mode mode) { mMode = mode; }
		Mode getMode() { return mMode; }

	private:
		struct RenderData
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLuint spacing;
			GLuint heightScale;
			GLuint blockSize;
			GLuint blockIndex;
		} mUniforms;
		
		World *mWorld;
		QOpenGLShaderProgram mProgram;
		QOpenGLVertexArrayObject mVao;
		GLuint mTexture;
		GLuint mTextureSand;

		Mode mMode;

		float mSpacing, mHeightScale;
		int mBlockSize;
		static const GLuint PrimitiveRestartIndex = 900000000;
		typedef std::vector<GLuint> IndexData;
		std::vector<IndexData> mIndexDataList;


	private:
		void loadShaders();
		void loadTextures();

		void buildIndexBlock(IndexData &indexData, int heightMapSize, int blockSize);
		void buildIndexData();

		void uploadTerrainData();
		void uploadVertexData();
		void uploadIndexData();

		struct LodIndexBlock
		{
			int count, offset;
			LodIndexBlock() : count(0), offset(0) {}
		};

		LodIndexBlock lodIndexBlockForLod(unsigned lod);
		Vec2i cameraPosToBlockPosition(Vec3f cameraPos);
	};
};

#endif

