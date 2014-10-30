//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_TERRAIN_RENDERER_INDEX_DATA_H
#define _t3d_TERRAIN_RENDERER_INDEX_DATA_H

#include <Main.h>
#include <World/World.h>
#include <World/TerrainRenderer.h>

namespace t3d
{
	const GLuint PrimitiveRestartIndex = 900000000;

	typedef GLubyte VertexEliminations;

	enum class VertexElimination
	{
		None	= 0x0000,
		Top		= 0x0001,
		Right	= 0x0010,
		Bottom	= 0x0100,
		Left	= 0x1000
	};


	struct LodIndexBlock
	{
		int count, offset;
		LodIndexBlock() : count(0), offset(0) {}
	};


	class TerrainRenderer::IndexData : protected OpenGLFunctions
	{
	public:
		IndexData(World *world, QOpenGLShaderProgram *program);

		void queryUniforms();
		LodIndexBlock lodIndexBlockForLod(unsigned lod, VertexEliminations vertexEliminations);
		void uploadIndexData();

		float spacing() { return mSpacing; }
		float heightScale() { return mHeightScale; }
		int blockSize() { return mBlockSize; }

	private:
		IndexData();

		World *mWorld;
		QOpenGLShaderProgram *mProgram;

		typedef std::vector<GLuint> RawIndicies;
		std::vector<RawIndicies> mIndexDataList;

		float mSpacing, mHeightScale;
		int mBlockSize;

		void buildIndexPatch(RawIndicies &rawIndicies, int heightMapSize, int patchSize, VertexEliminations vertexEliminations);
		void buildIndexData();
	};
}

#endif
