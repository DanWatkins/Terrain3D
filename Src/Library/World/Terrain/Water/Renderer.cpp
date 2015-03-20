//==================================================================================================================|
// Created 2015.03.08 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Core/Image.h>
#include "Renderer.h"

namespace t3d { namespace world { namespace terrain { namespace water
{
	void Renderer::init(Data *terrainData)
	{
		mTerrainData = terrainData;
		ShaderProgram::init();

		ShaderProgram::bind();
		{
			glPatchParameteri(GL_PATCH_VERTICES, 4);
			loadTextures();
		}
		ShaderProgram::release();

		//connect to terrainData signals
		{
			QObject::connect(terrainData, &Data::heightMapChanged, [this]()
			{
				this->mInvalidations.terrainData = true;
			});

			#define CONNECT_PROPERTY_TO_UNIFORM(prop, uniform) \
						mTerrainData->prop.connectToOnChanged([this]() \
						{ \
							this->enqueueUniformValueChange(&this->mUniforms.uniform, \
														 this->mTerrainData->prop); \
						});

				CONNECT_PROPERTY_TO_UNIFORM(pHeightScale, heightScale)
				CONNECT_PROPERTY_TO_UNIFORM(pSpanSize, spanSize)
			#undef CONNECT_PROPERTY_TO_UNIFORM
		}

		mElapsedTimer.start();
	}


	void Renderer::refresh()
	{
		if (mInvalidations.terrainData)
			queryUniformLocations();
	}


	void Renderer::cleanup()
	{
		ShaderProgram::raw().removeAllShaders();
		glDeleteTextures(1, &mTextures.water);
	}


	void Renderer::render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix)
	{
		ShaderProgram::bind();
		{
			glUniformMatrix4fv(mUniforms.mvMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
			glUniformMatrix4fv(mUniforms.projMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

			ShaderProgram::raw().setUniformValue(mUniforms.timeDelta, int(mElapsedTimer.elapsed()));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mTextures.water);

			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
		}
		ShaderProgram::release();
	}


///// PRIVATE
	void Renderer::addShaders()
	{
		addShader("/water/water.vs.glsl", QOpenGLShader::Vertex);
		addShader("/water/water.fs.glsl", QOpenGLShader::Fragment);
	}


	void Renderer::queryUniformLocations()
	{
		ShaderProgram::bind();
		{
			#define ULOC(id) mUniforms.id = ShaderProgram::raw().uniformLocation(#id)
			ULOC(mvMatrix);
			ULOC(projMatrix);
			ULOC(size);
			ULOC(spanSize);
			ULOC(heightScale);
			ULOC(waterLevel);
			ULOC(timeDelta);
			#undef ULOC

			ShaderProgram::raw().setUniformValue(mUniforms.size, mTerrainData->heightMap().size());
			ShaderProgram::raw().setUniformValue(mUniforms.spanSize, mTerrainData->pSpanSize);
			ShaderProgram::raw().setUniformValue(mUniforms.heightScale, mTerrainData->pHeightScale);
			ShaderProgram::raw().setUniformValue(mUniforms.waterLevel, pWaterLevel);
		}
		ShaderProgram::release();
	}


	void Renderer::loadTextures()
	{
		glGenTextures(1, &mTextures.water);
		{
			Image imageWater;
			imageWater.loadFromFile_PNG(gDefaultPathTextures + "water.png");

		

			int imageSize = imageWater.getWidth();	//for now, assume all images are the same width and height

			glBindTexture(GL_TEXTURE_2D, mTextures.water);

			int mipLevels = 8;
			glTexStorage2D(GL_TEXTURE_2D, mipLevels, GL_RGBA8, imageSize, imageSize);

			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageSize, imageSize,
							GL_RGBA, GL_UNSIGNED_BYTE, &imageWater.getImageData()[0]);

			glGenerateMipmap(GL_TEXTURE_2D);
			glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}
}}}}