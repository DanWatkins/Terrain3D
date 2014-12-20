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
#include <World/Terrain/Renderer.h>

namespace t3d { namespace World { namespace Terrain
{
	const GLuint PrimitiveRestartIndex = 900000000;
	const GLubyte VertexEliminationCombinations = 16;

	typedef GLubyte VertexElimination;

	const GLubyte VertexEliminationNone		= 0x0000; // b2 0000
	const GLubyte VertexEliminationTop		= 0x0001; // b2 0001
	const GLubyte VertexEliminationRight	= 0x0002; // b2 0010
	const GLubyte VertexEliminationBottom	= 0x0004; // b2 0100
	const GLubyte VertexEliminationLeft		= 0x0008;  // b2 1000


	struct LodIndexBlock
	{
		int count, offset;
		LodIndexBlock() : count(0), offset(0) {}
	};


	class Renderer::IndexData : protected OpenGLFunctions
	{
	public:
		IndexData(QOpenGLShaderProgram *program);

		void init(Data *terrainData, float spacing, float heightScale,
				  int blockSize, int spanSize);
		void cleanup();

		void queryUniforms();
		LodIndexBlock lodIndexBlockForLod(unsigned lod, VertexElimination vertexEliminations);
		void uploadIndexData();

		float spacing() { return mSpacing; }
		float heightScale() { return mHeightScale; }
		int blockSize() { return mBlockSize; }
		int spanSize() { return mSpanSize; }

	private:
		IndexData();

		Data *mTerrainData;
		QOpenGLShaderProgram *mProgram;
		GLuint mIbo;

		typedef QVector<GLuint> RawIndicies;
		QVector<RawIndicies> mIndexDataList;

		float mSpacing, mHeightScale;
		int mBlockSize, mSpanSize;

		void buildIndexPatch(RawIndicies &rawIndicies, int heightMapSize, int patchSize, VertexElimination vertexEliminations);
		void buildIndexData();
	};
}}}

#endif
