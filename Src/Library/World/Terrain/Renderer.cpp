//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Core/Image.h>
#include <World/Terrain/Renderer.h>
#include "IndexData.h"
#include "Utility.h"

namespace t3d { namespace World { namespace Terrain
{
	Renderer::Renderer(OpenGLWindow *window, Data *terrainData) :
		mTerrainData(terrainData),
		mProgram(window),
		mMode(Mode::Normal)
	{
		mRenderData = std::unique_ptr<IndexData>(new IndexData(mTerrainData, &mProgram));
		
	}


	Renderer::~Renderer()
	{
	}


	void Renderer::init()
	{
		initializeOpenGLFunctions();
		loadShaders();
		
		mProgram.bind();
		{
			mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
			mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
			mUniforms.spacing = mProgram.uniformLocation("spacing");
			mUniforms.heightScale = mProgram.uniformLocation("heightScale");
			mUniforms.heightMapSize = mProgram.uniformLocation("heightMapSize");
			mUniforms.blockSize = mProgram.uniformLocation("blockSize");
			mUniforms.spanSize = mProgram.uniformLocation("spanSize");
			mUniforms.blockIndex = mProgram.uniformLocation("blockIndex");
			mUniforms.textureMapResolution = mProgram.uniformLocation("textureMapResolution");
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


	Vec2i Renderer::cameraPosToBlockPosition(Vec3f cameraPos)
	{
		double blocksPerMapEdge = mRenderData->blockSize();

		Vec2i pos;
		pos.x = int(cameraPos.x / blocksPerMapEdge + 0.5) - 1;
		pos.y = int(cameraPos.z / blocksPerMapEdge + 0.5) - 1;

		return pos;
	}


	void Renderer::render(Vec3f cameraPos, Mat4 totalMatrix)
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
							   glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			mVao.bind();
			{
				int heightMapSize = mTerrainData->heightMap().size();
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

				//calculate the lod for every block
				QVector<QVector<int>> blockLod(numberOfBlocksOnASide, QVector<int>(numberOfBlocksOnASide, 0));

				for (int y=0; y<numberOfBlocksOnASide; y++)
				{
					for (int x=0; x<numberOfBlocksOnASide; x++)
					{
						blockLod[x][y] = lodForDistance(lodDistanceBetweenPos(cameraPosToBlockPosition(cameraPos), Vec2i(x,y), mRenderData->blockSize()), mRenderData->blockSize());
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
						block.lod = blockLod[x][y];
						block.baseVertex = offsetX+offsetY;

						block.neighborLod.left = blockLod[std::max(x-1, 0)][y];
						block.neighborLod.right = blockLod[std::min(x+1, int(blockLod.size())-1)][y];
						block.neighborLod.top = blockLod[x][std::max(y-1, 0)];
						block.neighborLod.bottom = blockLod[x][std::min(y+1, int(blockLod[x].size())-1)];

						renderBlock(block);
					}
				}
			}
			mVao.release();
		}
		mProgram.release();
	}


///// PRIVATE

	void Renderer::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, (QString(gDefaultPathShaders) + "camera-vert.glsl"));
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, (QString(gDefaultPathShaders) + "camera-frag.glsl"));

		if (mProgram.link() == false)
			printf("Problem linking shaders\n");
		else
			printf("Initialized shaders\n");
	}


	void Renderer::loadTextures()
	{
		glGenTextures(1, &mTexture[0]);
		glBindTexture(GL_TEXTURE_BUFFER, mTexture[0]);
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_TEXTURE_BUFFER, buffer);
			{
				glBufferData(GL_TEXTURE_BUFFER, sizeof(GLubyte)*mTerrainData->textureIndicies().size(), &mTerrainData->textureIndicies()[0], GL_STATIC_DRAW);
				glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, buffer);
			}
		}


		glActiveTexture(GL_TEXTURE1);
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

			glGenTextures(1, &mTexture[1]);
			glBindTexture(GL_TEXTURE_2D_ARRAY, mTexture[1]);

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
			glSamplerParameteri(mTexture[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri(mTexture[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}


	void Renderer::uploadTerrainData()
	{
		uploadVertexData();
		mRenderData->uploadIndexData();

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(PrimitiveRestartIndex);
	}


	void Renderer::uploadVertexData()
	{
		mTerrainData->heightMap().buildVertexData(mRenderData->spacing());
		mProgram.setUniformValue(mUniforms.spacing, mRenderData->spacing());
		mProgram.setUniformValue(mUniforms.heightMapSize, mTerrainData->heightMap().size());
		mProgram.setUniformValue(mUniforms.heightScale, mRenderData->heightScale());
		mProgram.setUniformValue(mUniforms.blockSize, float(mRenderData->blockSize()));
		mProgram.setUniformValue(mUniforms.spanSize, float(mRenderData->spanSize()));
		mProgram.setUniformValue(mUniforms.textureMapResolution, mTerrainData->textureMapResolution());
		const QVector<float> *terrainVertexData = mTerrainData->heightMap().getVertexData();

		GLuint vbo[2];
		glGenBuffers(2, vbo);

		//vertex data
		{
			//position
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			{
				GLuint size = sizeof(GLfloat)*terrainVertexData->size();
				glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);
			}
			//lighting brightness
			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			{
				GLuint size = sizeof(LightMap::ValueType) * mTerrainData->lightMap().raw()->size();
				glBufferData(GL_ARRAY_BUFFER, size, &mTerrainData->lightMap().raw()->at(0), GL_STATIC_DRAW);

				glVertexAttribIPointer(1, 1, GL_UNSIGNED_SHORT, 0, NULL);
				glEnableVertexAttribArray(1);
			}
		}
	}


	void Renderer::renderBlock(const Block &block)
	{
		glUniform2i(mUniforms.blockIndex, block.x, block.y);

		int patchSize = std::pow(2, block.lod+1);
		int patchesPerEdge = mRenderData->blockSize() / patchSize;
		int heightMapSize = mTerrainData->heightMap().size();

		//render all the patches (triangle fans) that make up this block
		for (int y=0; y<patchesPerEdge; y++)
		{
			int offsetY = y * patchSize * heightMapSize;

			for (int x=0; x<patchesPerEdge; x++)
			{
				VertexElimination ve = VertexEliminationNone;

				//request elimination of vertecies to blend with a higher lod neighbor
				if (x == 0  &&  block.neighborLod.left > block.lod)
					ve = ve | VertexEliminationLeft;
				if (x == patchesPerEdge-1  &&  block.neighborLod.right > block.lod)
					ve = ve | VertexEliminationRight;
				if (y == 0  &&  block.neighborLod.top > block.lod)
					ve = ve | VertexEliminationTop;
				if (y == patchesPerEdge-1  &&  block.neighborLod.bottom > block.lod)
					ve = ve | VertexEliminationBottom;

				LodIndexBlock lib;
				lib = mRenderData->lodIndexBlockForLod(block.lod, GLubyte(ve));

				int offsetX = x * patchSize;
				int baseVertex = block.baseVertex+offsetX+offsetY;



				glDrawElementsBaseVertex(GL_TRIANGLE_FAN, lib.count, GL_UNSIGNED_INT, (void*)lib.offset, baseVertex);
			}
		}
	}
}}}
