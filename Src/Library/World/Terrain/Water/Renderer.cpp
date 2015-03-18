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
	void Renderer::init(Data *terrainData, float waterLevel)
	{
		initializeOpenGLFunctions();
		mTerrainData = terrainData;
		mWaterLevel = waterLevel;
		loadShaders();

		mProgram->bind();
		{
			glPatchParameteri(GL_PATCH_VERTICES, 4);
			loadTextures();
		}
		mProgram->release();

		mElapsedTimer.start();
	}


	void Renderer::cleanup()
	{
		mProgram->removeAllShaders();
		glDeleteTextures(1, &mTextures.water);
	}


	void Renderer::render(Vec3f cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix)
	{
		mProgram->bind();
		{
			glUniformMatrix4fv(mUniforms.mvMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
			glUniformMatrix4fv(mUniforms.projMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

			mProgram->setUniformValue(mUniforms.timeDelta, int(mElapsedTimer.elapsed()));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mTextures.water);

			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
		}
		mProgram->release();
	}


	void Renderer::reloadShaders()
	{
		loadShaders();
	}


///// PRIVATE
	void Renderer::loadShader(const QString &filename, QOpenGLShader::ShaderType shaderType)
	{	//TODO move this function into a common base class since it's used in a lot of other places
		QOpenGLShader *shader = new QOpenGLShader(shaderType, mProgram.get());
		if (!shader->compileSourceFile(gDefaultPathShaders + "/water/" + filename))
			qDebug() << "Error compiling shader " << filename << " of type " << static_cast<int>(shaderType);
		
		if (!mProgram->addShader(shader))
			qDebug() << "Error adding shader " << filename << " of type " << static_cast<int>(shaderType);
	}


	void Renderer::loadShaders()
	{
		mProgram = std::make_unique<QOpenGLShaderProgram>();

		loadShader("water.vs.glsl", QOpenGLShader::Vertex);
		loadShader("water.fs.glsl", QOpenGLShader::Fragment);

		if (mProgram->link() == false)
			qFatal("Problem linking shaders");
		else
			qDebug() << "Initialized shaders";

		mProgram->bind();
		{
			#define ULOC(id) mUniforms.id = mProgram->uniformLocation(#id)
			ULOC(mvMatrix);
			ULOC(projMatrix);
			ULOC(size);
			ULOC(spanSize);
			ULOC(waterLevel);
			ULOC(timeDelta);
			#undef ULOC

			mProgram->setUniformValue(mUniforms.size, mTerrainData->heightMap().size());
			mProgram->setUniformValue(mUniforms.spanSize, mTerrainData->pSpanSize);
			mProgram->setUniformValue(mUniforms.waterLevel, mWaterLevel);
		}
		mProgram->release();
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