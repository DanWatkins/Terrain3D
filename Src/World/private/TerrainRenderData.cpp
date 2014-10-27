//==================================================================================================================|
// Created 2014.10.27 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "TerrainRenderData.h"

namespace t3d
{
	TerrainRenderData::TerrainRenderData() :
		mWorld(nullptr),
		mProgram(nullptr),
		mSpacing(1.0f),
		mHeightScale(75.0f),
		mBlockSize(8)
	{
	}

	TerrainRenderData::TerrainRenderData(World *world, QOpenGLShaderProgram *program) :
		TerrainRenderData()
	{
		mWorld = world;
		mProgram = program;
	}


	void TerrainRenderData::queryUniforms()
	{
		initializeOpenGLFunctions();

		mUniforms.matrixCamera = mProgram->uniformLocation("cameraMatrix");
		mUniforms.matrixModel = mProgram->uniformLocation("modelMatrix");
		mUniforms.spacing = mProgram->uniformLocation("spacing");
		mUniforms.heightScale = mProgram->uniformLocation("heightScale");
		mUniforms.blockSize = mProgram->uniformLocation("blockSize");
		mUniforms.blockIndex = mProgram->uniformLocation("blockIndex");
	}


	void TerrainRenderData::updateTotalMatrix(Mat4 totalMatrix)
	{
		glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
		glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
								glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));
	}


	void TerrainRenderData::updateBlockIndex(int x, int y)
	{
		glUniform2i(mUniforms.blockIndex, x, y);
	}


	LodIndexBlock TerrainRenderData::lodIndexBlockForLod(unsigned lod)
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


	void TerrainRenderData::buildIndexBlock(IndexData &indexData, int heightMapSize, int blockSize)
	{
		int mapSize = ceil(double(heightMapSize-1) / double(mBlockSize));
		int mapSizeVertex = mapSize*mBlockSize + 1;

		indexData.clear();
		indexData.reserve((blockSize+1) * ((blockSize+1)*2 + 1));

		for (int y=0; y<blockSize; y++)
		{
			int scale = mBlockSize / blockSize;
			int offset = y*mapSizeVertex*scale;
			

			for (int x=0; x<blockSize+1; x++)
			{
				indexData.push_back(x*scale + offset);
				indexData.push_back(x*scale + mapSizeVertex*scale + offset);
			}

			indexData.push_back(PrimitiveRestartIndex);
		}
	}


	int maxLevelsOfDetail(int blockSize)
	{
		return 1 + int(std::log10(blockSize)/std::log10(2));
	}


	int sizeForLod(int lod)
	{
		return std::pow(2, lod);
	}


	void TerrainRenderData::buildIndexData()
	{
		std::cout << "Generating index data set" << std::endl;

		int heightMapSize = mWorld->getHeightMap().getSize();
		int lod = maxLevelsOfDetail(mBlockSize);

		for (int i=0; i<lod; i++)
		{
			mIndexDataList.push_back(IndexData());
			buildIndexBlock(mIndexDataList.back(), heightMapSize, sizeForLod(i));
		}
	}


	void TerrainRenderData::uploadTerrainData()
	{
		uploadVertexData();
		uploadIndexData();

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(PrimitiveRestartIndex);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}


	void TerrainRenderData::uploadVertexData()
	{
		GLuint vbo;
		mWorld->getHeightMap().buildVertexData(mSpacing);
		mProgram->setUniformValue(mUniforms.spacing, mSpacing);
		mProgram->setUniformValue(mUniforms.heightScale, mHeightScale);
		mProgram->setUniformValue(mUniforms.blockSize, float(mBlockSize));
		const std::vector<float> *terrainVertexData = mWorld->getHeightMap().getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint size = sizeof(float)*terrainVertexData->size();
		glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);
	}


	void TerrainRenderData::uploadIndexData()
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
			IndexData *indexData = &mIndexDataList[i];
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, previousOffset, sizeof(GLuint)*mIndexDataList[i].size(), &mIndexDataList[i][0]);

			previousOffset += indexData->size() * sizeof(GLuint);
		}
	}
}