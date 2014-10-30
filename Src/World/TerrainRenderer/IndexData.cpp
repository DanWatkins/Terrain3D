//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "IndexData.h"

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


	void TerrainRenderer::IndexData::buildIndexBlock(RawIndicies &rawIndicies, int heightMapSize, int blockSize)
	{
		int mapSize = ceil(double(heightMapSize-1) / double(mBlockSize));
		int mapSizeVertex = mapSize*mBlockSize + 1;

		rawIndicies.clear();
		rawIndicies.reserve((blockSize+1) * ((blockSize+1)*2 + 1));

		for (int y=0; y<blockSize; y++)
		{
			int scale = mBlockSize / blockSize;
			int offset = y*mapSizeVertex*scale;
			

			for (int x=0; x<blockSize+1; x++)
			{
				rawIndicies.push_back(x*scale + offset);
				rawIndicies.push_back(x*scale + mapSizeVertex*scale + offset);
			}

			rawIndicies.push_back(PrimitiveRestartIndex);
		}
	}


	int maxLevelsOfDetail(int blockSize)
	{
		return 1 + int(std::log10(blockSize)/std::log10(2) + 0.5);
	}


	int sizeForLod(int lod)
	{
		return std::pow(2, lod);
	}


	void TerrainRenderer::IndexData::buildIndexData()
	{
		std::cout << "Generating index data set" << std::endl;

		int heightMapSize = mWorld->getHeightMap().getSize();
		int lod = maxLevelsOfDetail(mBlockSize);

		for (int i=0; i<lod; i++)
		{
			mIndexDataList.push_back(RawIndicies());
			buildIndexBlock(mIndexDataList.back(), heightMapSize, sizeForLod(i));
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
