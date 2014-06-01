//=======================================================================================================================|
// Created 2014.05.31 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Texture.h"
#include "Shader.h"

void genTex(float *data, int width, int height)
{
	int x, y;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 63.0f;
			data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 127.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}


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


	void Texture::init()
	{
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 256, 256);

		float *data = new float[256*256*4];
		genTex(data, 256, 256);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA, GL_FLOAT, data);
		delete[] data;

		loadShaders();

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
	}


	void Texture::render()
	{		
		glUseProgram(mProgram);
		glBindVertexArray(mVao);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);
	}


	void Texture::unloadTexure()
	{
		glDeleteTextures(1, &mTexture);
	}
};