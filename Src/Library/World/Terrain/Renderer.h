//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAIN_RENDERER_H
#define _t3d_TERRAIN_RENDERER_H

#include <Main.h>
#include <World/Terrain/Data.h>

namespace t3d { namespace World { namespace Terrain
{
	enum class Mode
	{
		Normal,
		WireFrame
	};


	class Renderer : protected OpenGLFunctions
	{
	public:
		Renderer(Data *terrainData);
		~Renderer();

		void init();
		void render(Vec3f cameraPos, Mat4 totalMatrix);

		void setMode(Mode mode) { mMode = mode; }
		Mode getMode() { return mMode; }

	private:
		Q_DISABLE_COPY(Renderer)
		class IndexData;
		std::unique_ptr<IndexData> mRenderData;

		Data *mTerrainData;
		QOpenGLShaderProgram mProgram;
		QOpenGLVertexArrayObject mVao;
		GLuint mTexture[2];
		Mode mMode;

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLuint spacing;
			GLuint heightScale;
			GLuint heightMapSize;
			GLuint blockSize;
			GLuint spanSize;
			GLuint blockIndex;
			GLuint textureMapResolution;
		} mUniforms;

		struct Block
		{
			int x, y;
			int lod, baseVertex;

			struct NeighborLod
			{
				int top, right, bottom, left;
				NeighborLod() : top(0), right(0), bottom(0), left(0) {}
			} neighborLod;

			Block() : x(0), y(0), lod(0), baseVertex(0) {}
		};

	private:
		void loadShaders();
		void loadTextures();
		Vec2i cameraPosToBlockPosition(Vec3f cameraPos);

		void uploadTerrainData();
		void uploadVertexData();
		void renderBlock(const Block &block);
	};
}}}

#endif

