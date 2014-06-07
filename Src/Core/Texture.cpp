//=======================================================================================================================|
// Created 2014.05.31 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Texture.h"
#include "Shader.h"

namespace t3d
{
	Texture::Texture()
	{
		mProgram = 0;
		mTexture = 0;
	}


	Texture::~Texture()
	{
		glDeleteProgram(mProgram);
		glDeleteVertexArrays(1, &mVao);
	}


	void Texture::loadShaders()
	{
		Uint shaders[2];
		shaders[0] = Shader::loadShader(String(gDefaultPathShaders) + "texture-vert.glsl", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(String(gDefaultPathShaders) + "texture-frag.glsl", GL_FRAGMENT_SHADER);

		mProgram = Shader::linkFromShaders(shaders, 2);
	}


	void Texture::initWithImage(const Image &image)
	{
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, image.getWidth(), image.getHeight());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, &image.getImageData()[0]);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		Uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		const float vertexPositions[] =
		{
			0.f, 0.f, 0.0f, 1.f,
			1.f, 0.f, 0.0f, 1.f,
			1.f, 1.f, 0.0f, 1.f,
			
			0.f, 0.f, 0.0f, 1.f,
			1.f, 1.f, 0.0f, 1.f,
			0.f, 1.f, 0.0f, 1.f,


			0.f, 0.f, 0.f, 0.f,
			1.f, 0.f, 0.f, 0.f,
			1.f, 1.f, 0.f, 0.f,

			0.f, 0.f, 0.f, 0.f,
			1.f, 1.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glEnableVertexAttribArray(1);
		Int texturePosOffset = sizeof(vertexPositions)/2;
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)texturePosOffset);

		loadShaders();

		glBindVertexArray(0);
	}


	void Texture::render() const
	{
		glUseProgram(mProgram);
		glBindVertexArray(mVao);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		glBindVertexArray(0);
		glUseProgram(0);
	}


	void Texture::unloadTexure() const
	{
		glDeleteTextures(1, &mTexture);
	}
};