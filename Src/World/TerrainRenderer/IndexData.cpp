//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "IndexData.h"
#include "Utility.h"

namespace t3d
{
	TerrainRenderer::IndexData::IndexData() :
		mWorld(nullptr),
		mProgram(nullptr),
		mSpacing(1.0f),
		mHeightScale(75.0f),
		mBlockSize(8)
	{
	}

	TerrainRenderer::IndexData::IndexData(World *world, QOpenGLShaderProgram *program) :
		IndexData()
	{
		mWorld = world;
		mProgram = program;
	}


	void TerrainRenderer::IndexData::queryUniforms()
	{
		initializeOpenGLFunctions();
	}


	LodIndexBlock TerrainRenderer::IndexData::lodIndexBlockForLod(unsigned lod, VertexEliminations vertexEliminations)
	{
		LodIndexBlock lib;

		for (unsigned i=0; i<mIndexDataList.size(); i++)
		{
			if (lod == i)
			{
				lib.count = mIndexDataList[i].size();
				break;
			}
			else
			{ 
				lib.offset += mIndexDataList[i].size()*sizeof(GLuint);
			}
		}

		return lib;
	}


	bool is(VertexEliminations ve, VertexElimination ves)
	{
		return (static_cast<GLubyte>(ve) & static_cast<GLubyte>(ves)) == static_cast<GLubyte>(ves);
	}


	void TerrainRenderer::IndexData::buildIndexPatch(RawIndicies &rawIndicies, int heightMapSize, int patchSize, VertexEliminations vertexEliminations)
	{
		std::cout << "    Building Index Patch: size=" << patchSize << " eliminating=";

		rawIndicies.clear();
		rawIndicies.reserve(5 + int(!is(vertexEliminations, VertexElimination::Top))
							+ int(!is(vertexEliminations, VertexElimination::Right))
							+ int(!is(vertexEliminations, VertexElimination::Bottom))
							+ int(!is(vertexEliminations, VertexElimination::Left)));

		int scale = patchSize/2;
		int scaledMapSize = scale*heightMapSize;

		int center = scaledMapSize + scale;
		rawIndicies.push_back(center);

		if (!is(vertexEliminations, VertexElimination::Right))
			rawIndicies.push_back(center+scale);

		rawIndicies.push_back(center+scale+scaledMapSize);

		if (!is(vertexEliminations, VertexElimination::Bottom))
			rawIndicies.push_back(center + scaledMapSize);

		rawIndicies.push_back(center - scale + scaledMapSize);

		if (!is(vertexEliminations, VertexElimination::Left))
			rawIndicies.push_back(center-scale);

		rawIndicies.push_back(center - scale - scaledMapSize);

		if (!is(vertexEliminations, VertexElimination::Top))
			rawIndicies.push_back(center - scaledMapSize);

		rawIndicies.push_back(center + scale - scaledMapSize);
		rawIndicies.push_back(PrimitiveRestartIndex);
	}


	void TerrainRenderer::IndexData::buildIndexData()
	{
		std::cout << "Generating index data set" << std::endl;

		int heightMapSize = mWorld->getHeightMap().getSize();
		int lod = maxLevelsOfDetail(mBlockSize);

		for (int i=0; i<lod; i++)
		{
			const GLubyte VertexEliminationCombinations = 16;
			std::cout << "  Building Index Data: lod=" << i << std::endl;

			for (GLubyte j=0; j<VertexEliminationCombinations; j++)
			{
				mIndexDataList.push_back(RawIndicies());
				buildIndexPatch(mIndexDataList.back(), heightMapSize, sizeForLod(i), j);
			}
		}
	}


	void TerrainRenderer::IndexData::uploadIndexData()
	{
		GLuint ibo;
		buildIndexData();


		int reserve = 0;
		for (unsigned i=0; i<mIndexDataList.size(); i++)
			reserve += mIndexDataList[i].size()*sizeof(GLuint);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, reserve, NULL, GL_STATIC_DRAW);

		int previousOffset = 0;
		for (unsigned i=0; i<mIndexDataList.size(); i++)
		{
			RawIndicies *indexData = &mIndexDataList[i];
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, previousOffset, sizeof(GLuint)*mIndexDataList[i].size(), &mIndexDataList[i][0]);

			previousOffset += indexData->size() * sizeof(GLuint);
		}
	}
}
