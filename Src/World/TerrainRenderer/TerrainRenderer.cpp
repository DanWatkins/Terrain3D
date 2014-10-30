//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Core/Image.h>
#include <World/TerrainRenderer.h>
#include "IndexData.h"

namespace t3d
{
	TerrainRenderer::TerrainRenderer(OpenGLWindow *window, World *world) :
		mWorld(world),
		mProgram(window),
		mMode(Mode::Normal)
	{
		mRenderData = std::unique_ptr<IndexData>(new IndexData(mWorld, &mProgram));
		
	}


	TerrainRenderer::~TerrainRenderer()
	{
	}


	void TerrainRenderer::init()
	{
		initializeOpenGLFunctions();
		loadShaders();
		
		mProgram.bind();
		{
			mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
			mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
			mUniforms.spacing = mProgram.uniformLocation("spacing");
			mUniforms.heightScale = mProgram.uniformLocation("heightScale");
			mUniforms.blockSize = mProgram.uniformLocation("blockSize");
			mUniforms.blockIndex = mProgram.uniformLocation("blockIndex");
			mRenderData->queryUniforms();

			mVao.create();
			mVao.bind();
			{
				uploadTerrainData();
				loadTextures();
			}
			mVao.release();
		}
		mProgram.release();
	}


	Vec2i TerrainRenderer::cameraPosToBlockPosition(Vec3f cameraPos)
	{
		double blocksPerMapEdge = mRenderData->blockSize();

		Vec2i pos;
		pos.x = int(cameraPos.x / blocksPerMapEdge + 0.5) - 1;
		pos.y = int(cameraPos.z / blocksPerMapEdge + 0.5) - 1;

		return pos;
	}


	double blockDistanceBetweenPos(Vec2i a, Vec2i b)
	{
		Vec2i net(a.x-b.x, a.y-b.y);

		return std::sqrt(net.x*net.x + net.y*net.y);
	}


	int lodForDistance(double distance)
	{
		if (distance > 30.0)
			return 0;
		if (distance > 20.0)
			return 1;
		if (distance > 10.0)
			return 2;

		return 3;
	}


	void TerrainRenderer::render(Vec3f cameraPos, Mat4 totalMatrix)
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
							   glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			mVao.bind();
			{
				int heightMapSize = mWorld->getHeightMap().getSize();
				int numberOfBlocksOnASide = ceil(double(heightMapSize-1) / double(mRenderData->blockSize()));
				switch (mMode)
				{
					case Mode::Normal:
					{
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						break;
					}

					case Mode::WireFrame:
					{
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						break;
					}
				}

				//render all of the blocks
				for (int y=0; y<numberOfBlocksOnASide; y++)
				{
					int offsetY = y * (mRenderData->blockSize()*numberOfBlocksOnASide + 1)*mRenderData->blockSize();

					for (int x=0; x<numberOfBlocksOnASide; x++)
					{
						int offsetX = x*mRenderData->blockSize();

						Block block;
						block.x = x;
						block.y = y;
						block.lod = lodForDistance(blockDistanceBetweenPos(cameraPosToBlockPosition(cameraPos), Vec2i(x,y)));
						block.baseVertex = offsetX+offsetY;

						//TODO compute levels of detail for neighbor blocks
						//for now, pretend all neighbors are the same level of detail (will cause cracks)
						block.neighborLod.top = block.neighborLod.right = block.neighborLod.bottom = block.neighborLod.left = block.lod;

						renderBlock(block);
					}
				}
			}
			mVao.release();
		}
		mProgram.release();
	}


///// PRIVATE

	void TerrainRenderer::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, (String(gDefaultPathShaders) + "camera-vert.glsl").c_str());
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, (String(gDefaultPathShaders) + "camera-frag.glsl").c_str());

		if (mProgram.link() == false)
			printf("Problem linking shaders\n");
		else
			printf("Initialized shaders\n");
	}


	void TerrainRenderer::loadTextures()
	{
		Image imageWater;
		imageWater.loadFromFile_PNG("./Textures/water.png");

		Image imageSand;
		imageSand.loadFromFile_PNG("./Textures/sand.png");

		Image imageGrass;
		imageGrass.loadFromFile_PNG("./Textures/grass.png");

		Image imageMountain;
		imageMountain.loadFromFile_PNG("./Textures/mountain.png");

		int imageSize = imageWater.getWidth();	//for now, assume all images are the same width and height

		glGenTextures(1, &mTextureSand);
		glBindTexture(GL_TEXTURE_2D_ARRAY, mTexture);

		int mipLevels = 8;
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevels, GL_RGBA8, imageSize, imageSize, 4);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
						0, 0, 0,
						imageSize, imageSize, 1,
						GL_RGBA, GL_UNSIGNED_BYTE, &imageWater.getImageData()[0]);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
						0, 0, 1,
						imageSize, imageSize, 1,
						GL_RGBA, GL_UNSIGNED_BYTE, &imageSand.getImageData()[0]);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
						0, 0, 2,
						imageSize, imageSize, 1,
						GL_RGBA, GL_UNSIGNED_BYTE, &imageGrass.getImageData()[0]);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
						0, 0, 3,
						imageSize, imageSize, 1,
						GL_RGBA, GL_UNSIGNED_BYTE, &imageMountain.getImageData()[0]);

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glSamplerParameteri(mTextureSand, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(mTextureSand, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}


	void TerrainRenderer::uploadTerrainData()
	{
		uploadVertexData();
		mRenderData->uploadIndexData();

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(PrimitiveRestartIndex);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}


	void TerrainRenderer::uploadVertexData()
	{
		GLuint vbo;
		mWorld->getHeightMap().buildVertexData(mRenderData->spacing());
		mProgram.setUniformValue(mUniforms.spacing, mRenderData->spacing());
		mProgram.setUniformValue(mUniforms.heightScale, mRenderData->heightScale());
		mProgram.setUniformValue(mUniforms.blockSize, float(mRenderData->blockSize()));
		const std::vector<float> *terrainVertexData = mWorld->getHeightMap().getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint size = sizeof(float)*terrainVertexData->size();
		glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);
	}


	void TerrainRenderer::renderBlock(const Block &block)
	{
		glUniform2i(mUniforms.blockIndex, block.x, block.y);

		int patchesPerEdge = mRenderData->blockSize() / (std::pow(2, block.lod+1));

		//glDrawElementsBaseVertex(GL_TRIANGLE_STRIP, lib.count, GL_UNSIGNED_INT, (void*)lib.offset, baseVertex);
	}
}
