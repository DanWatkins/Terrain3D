//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Core/Image.h>
#include <World/Terrain/Renderer.h>
#include "Utility.h"

namespace t3d { namespace world { namespace terrain
{
	void Renderer::init(Data *terrainData)
	{
		mTerrainData = terrainData;

		ShaderProgram::init();
		
		mWaterRenderer.init(mTerrainData, mTerrainData->heightScale()*0.30f);

		//connect to terrainData signals
		{
			QObject::connect(terrainData, &Data::heightMapChanged, [this]()
			{
				this->mInvalidations.heightMap = true;
			});

			QObject::connect(terrainData, &Data::lightMapChanged, [this]()
			{
				this->mInvalidations.lightMap =  true;
			});


#define CONNECT_LISTENER(signalFunc, propertyId) QObject::connect(terrainData, &Data::signalFunc, [this]() \
						{ \
							this->bindAndSetUniformValue(this->mUniforms.propertyId, \
							this->mTerrainData->propertyId()); \
						});

			CONNECT_LISTENER(textureMapResolutionChanged, textureMapResolution)
			CONNECT_LISTENER(heightScaleChanged, heightScale)
			CONNECT_LISTENER(spanSizeChanged, spanSize)
			CONNECT_LISTENER(chunkSizeChanged, chunkSize)

#undef CONNECT_LISTENER

			QObject::connect(terrainData, &Data::chunkSizeChanged, [this]() { qDebug() << "Hey"; });
		}
	}


	void Renderer::refreshIfNeeded()
	{
		auto work = [](std::function<void()> task, bool &conditional)
		{
			if (conditional)
			{
				task();
				conditional = false;
			}
		};

		work(std::bind(&Renderer::uploadHeightMap, this), mInvalidations.heightMap);
		work(std::bind(&Renderer::uploadLightMap, this), mInvalidations.lightMap);

		/*if (mInvalidations.heightMap)
		{
			uploadHeightMap();
			mInvalidations.heightMap = false;
		}

		if (mInvalidations.lightMap)
		{
			uploadLightMap();
			mInvalidations.lightMap = false;
		}*/
	}


	void Renderer::prepareForRendering()
	{
		ShaderProgram::raw().bind();
		{
			glGenVertexArrays(1, &mVao);
			glBindVertexArray(mVao);
			{
				uploadHeightMap();
				uploadLightMap();

				glPatchParameteri(GL_PATCH_VERTICES, 4);
				loadTextures();
			}
			glBindVertexArray(0);
		}
		ShaderProgram::raw().release();
	}


	void Renderer::cleanup()
	{
		mTerrainData->cleanup();
		mWaterRenderer.cleanup();

		ShaderProgram::raw().removeAllShaders();
		glDeleteBuffers(2, mVbo);
		glDeleteTextures(1, &mTextures.heightMap);
		glDeleteTextures(1, &mTextures.indicies);
		glDeleteTextures(1, &mTextures.terrain);
		glDeleteVertexArrays(1, &mVao);
	}


	void Renderer::render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix)
	{
		ShaderProgram::raw().bind();
		{
			glUniformMatrix4fv(mUniforms.mvMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
			glUniformMatrix4fv(mUniforms.projMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

			glBindVertexArray(mVao);
			{
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

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mTextures.heightMap);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, mTextures.lightMap);
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_BUFFER, mTextures.indicies);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D_ARRAY, mTextures.terrain);

				const int terrainSize = mTerrainData->heightMap().size();
				const int chunkSize = mTerrainData->chunkSize();
				const int chunksPerSide = terrainSize / chunkSize;

				glUniform3fv(mUniforms.cameraPos, 1, glm::value_ptr(cameraPos));
				ShaderProgram::raw().setUniformValue(mUniforms.lod, mLodFactor);
				ShaderProgram::raw().setUniformValue(mUniforms.ivd, mIvdFactor);

				glDrawArraysInstanced(GL_PATCHES, 0, 4, chunksPerSide*chunksPerSide);
			}

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(0);
		}
		ShaderProgram::raw().release();

		mWaterRenderer.render(cameraPos, modelViewMatrix, perspectiveMatrix);
	}


	void Renderer::reloadShaders()
	{
		loadShaders();
		mWaterRenderer.reloadShaders();
	}


///// PRIVATE
	void Renderer::addShaders()
	{
		addShader("terrain.vs.glsl", QOpenGLShader::Vertex);
		addShader("terrain.tcs.glsl", QOpenGLShader::TessellationControl);
		addShader("terrain.tes.glsl", QOpenGLShader::TessellationEvaluation);
		addShader("terrain.fs.glsl", QOpenGLShader::Fragment);
	}


	void Renderer::loadTextures()
	{
		glGenTextures(1, &mTextures.indicies);
		glBindTexture(GL_TEXTURE_BUFFER, mTextures.indicies);
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_TEXTURE_BUFFER, buffer);
			{
				glBufferData(GL_TEXTURE_BUFFER, sizeof(GLubyte)*mTerrainData->textureIndicies().size(), &mTerrainData->textureIndicies()[0], GL_STATIC_DRAW);
				glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, buffer);
			}
		}

		glGenTextures(1, &mTextures.terrain);
		{
			Image imageWater;
			imageWater.loadFromFile_PNG(gDefaultPathTextures + "dirt.png");

			Image imageSand;
			imageSand.loadFromFile_PNG(gDefaultPathTextures + "sand.png");

			Image imageGrass;
			imageGrass.loadFromFile_PNG(gDefaultPathTextures + "grass.png");

			Image imageMountain;
			imageMountain.loadFromFile_PNG(gDefaultPathTextures + "mountain.png");

			int imageSize = imageWater.getWidth();	//for now, assume all images are the same width and height

			glBindTexture(GL_TEXTURE_2D_ARRAY, mTextures.terrain);

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
			glSamplerParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}


	void Renderer::queryUniformLocations()
	{
		ShaderProgram::raw().bind();
		{
			#define ULOC(id) mUniforms.id = ShaderProgram::raw().uniformLocation(#id)
			ULOC(mvMatrix);
			ULOC(projMatrix);

			ULOC(terrainSize);
			ULOC(chunkSize);
			ULOC(lod);
			ULOC(ivd);
			ULOC(cameraPos);
			ULOC(heightScale);
			ULOC(spanSize);

			ULOC(textureMapResolution);
			ULOC(heightMapSize);
			#undef ULOC

			ShaderProgram::raw().setUniformValue(mUniforms.terrainSize, mTerrainData->heightMap().size());
			ShaderProgram::raw().setUniformValue(mUniforms.heightScale, mTerrainData->heightScale());
			ShaderProgram::raw().setUniformValue(mUniforms.spanSize, mTerrainData->spanSize());
			ShaderProgram::raw().setUniformValue(mUniforms.chunkSize, mTerrainData->chunkSize());
			ShaderProgram::raw().setUniformValue(mUniforms.textureMapResolution, mTerrainData->textureMapResolution());
			ShaderProgram::raw().setUniformValue(mUniforms.heightMapSize, mTerrainData->heightMap().size());
		}
		ShaderProgram::raw().release();
	}


	void Renderer::uploadHeightMap()
	{
		//height map
		{
			if (glIsTexture(mTextures.heightMap))
				glDeleteTextures(1, &mTextures.heightMap);

			glGenTextures(1, &mTextures.heightMap);
			glBindTexture(GL_TEXTURE_2D, mTextures.heightMap);

			const HeightMap &hm = mTerrainData->heightMap();
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, hm.size(), hm.size());
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, hm.size(), hm.size(), GL_RED, GL_FLOAT, hm.raw());

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
	}

	
	void Renderer::uploadLightMap()
	{
		//light map
		{
			if (glIsTexture(mTextures.lightMap))
				glDeleteTextures(1, &mTextures.lightMap);

			glGenTextures(1, &mTextures.lightMap);
			glBindTexture(GL_TEXTURE_2D, mTextures.lightMap);

			const LightMap &lm = mTerrainData->lightMap();
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, lm.size(), lm.size());
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, lm.size(), lm.size(), GL_RED, GL_UNSIGNED_SHORT, lm.raw());

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
	}
}}}