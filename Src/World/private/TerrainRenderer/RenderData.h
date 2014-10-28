//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAIN_RENDERER_RENDER_DATA_H
#define _t3d_TERRAIN_RENDERER_RENDER_DATA_H

#include <Main.h>
#include <World/World.h>
#include <World/TerrainRenderer.h>

namespace t3d
{
	struct LodIndexBlock
	{
		int count, offset;
		LodIndexBlock() : count(0), offset(0) {}
	};

	class TerrainRenderer::RenderData : protected QOpenGLFunctions_4_3_Core
	{
	public:
		RenderData(World *world, QOpenGLShaderProgram *program);

		void queryUniforms();
		void uploadTerrainData();
		LodIndexBlock lodIndexBlockForLod(unsigned lod);
		void updateTotalMatrix(Mat4 totalMatrix);
		void updateBlockIndex(int x, int y);

		int blockSize() { return mBlockSize; }

	private:
		RenderData();

		World *mWorld;
		QOpenGLShaderProgram *mProgram;

		typedef std::vector<GLuint> IndexData;
		std::vector<IndexData> mIndexDataList;
		static const GLuint PrimitiveRestartIndex = 900000000;

		float mSpacing, mHeightScale;
		int mBlockSize;

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLuint spacing;
			GLuint heightScale;
			GLuint blockSize;
			GLuint blockIndex;
		} mUniforms;

		void buildIndexBlock(IndexData &indexData, int heightMapSize, int blockSize);
		void buildIndexData();
		
		void uploadVertexData();
		void uploadIndexData();
	};
}

#endif
