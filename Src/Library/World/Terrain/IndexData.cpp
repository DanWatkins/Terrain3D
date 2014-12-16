//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "IndexData.h"
#include "Utility.h"

namespace t3d { namespace World { namespace Terrain
{
	Renderer::IndexData::IndexData() :
		mTerrainData(nullptr),
		mProgram(nullptr),
		mSpacing(1.0f),
		mHeightScale(30.0f),
		mBlockSize(64),
		mSpanSize(8)
	{
	}

	Renderer::IndexData::IndexData(Data *terrainData, QOpenGLShaderProgram *program) :
		IndexData()
	{
		mTerrainData = terrainData;
		mProgram = program;
	}


	void Renderer::IndexData::cleanup()
	{
		if (mIbo)
			glDeleteBuffers(1, &mIbo);
	}


	void Renderer::IndexData::queryUniforms()
	{
		initializeOpenGLFunctions();
	}


	LodIndexBlock Renderer::IndexData::lodIndexBlockForLod(unsigned lod, VertexElimination vertexEliminations)
	{
		LodIndexBlock lib;
		int searchIndex = lod*VertexEliminationCombinations + vertexEliminations;

		for (int i=0; i<mIndexDataList.size(); i++)
		{
			if (searchIndex == i)
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


	bool is(VertexElimination ve, VertexElimination ves)
	{
		return (static_cast<GLubyte>(ve) & static_cast<GLubyte>(ves)) == static_cast<GLubyte>(ves);
	}


	void Renderer::IndexData::buildIndexPatch(RawIndicies &rawIndicies, int heightMapSize, int patchSize, VertexElimination vertexEliminations)
	{
		rawIndicies.clear();
		rawIndicies.reserve(6 + int(!is(vertexEliminations, VertexEliminationTop))
							+ int(!is(vertexEliminations, VertexEliminationRight))
							+ int(!is(vertexEliminations, VertexEliminationBottom))
							+ int(!is(vertexEliminations, VertexEliminationLeft)));

		int scale = patchSize/2;
		int scaledMapSize = scale*heightMapSize;

		int center = scaledMapSize + scale;
		rawIndicies.push_back(center);

		if (!is(vertexEliminations, VertexEliminationRight))
			rawIndicies.push_back(center+scale);

		rawIndicies.push_back(center+scale+scaledMapSize);

		if (!is(vertexEliminations, VertexEliminationBottom))
			rawIndicies.push_back(center + scaledMapSize);

		rawIndicies.push_back(center - scale + scaledMapSize);

		if (!is(vertexEliminations, VertexEliminationLeft))
			rawIndicies.push_back(center-scale);

		rawIndicies.push_back(center - scale - scaledMapSize);

		if (!is(vertexEliminations, VertexEliminationTop))
			rawIndicies.push_back(center - scaledMapSize);

		rawIndicies.push_back(center + scale - scaledMapSize);
		rawIndicies.push_back(rawIndicies[1]);
		rawIndicies.push_back(PrimitiveRestartIndex);
	}


	void Renderer::IndexData::buildIndexData()
	{
		int heightMapSize = mTerrainData->heightMap().size();
		int lod = maxLevelsOfDetail(mBlockSize);

		for (int i=0; i<lod; i++)
		{
			for (GLubyte j=0; j<VertexEliminationCombinations; j++)
			{
				mIndexDataList.push_back(RawIndicies());
				buildIndexPatch(mIndexDataList.back(), heightMapSize, sizeForLod(i), j);
			}
		}
	}


	void Renderer::IndexData::uploadIndexData()
	{
		buildIndexData();

		int reserve = 0;
		for (int i=0; i<mIndexDataList.size(); i++)
			reserve += mIndexDataList[i].size()*sizeof(GLuint);

		glGenBuffers(1, &mIbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, reserve, NULL, GL_STATIC_DRAW);

		int previousOffset = 0;
		for (int i=0; i<mIndexDataList.size(); i++)
		{
			RawIndicies *indexData = &mIndexDataList[i];
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, previousOffset, sizeof(GLuint)*mIndexDataList[i].size(), &mIndexDataList[i][0]);

			previousOffset += indexData->size() * sizeof(GLuint);
		}
	}
}}}
