//==================================================================================================================|
// Created 2014.05.31 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Sprite.h"
#include "Shader.h"

namespace t3d
{
	Sprite::Sprite() :
		mScreenPos(0.0f, 0.0f, 0.0f),
		mScale(1.0f, 1.0f, 1.0f),
		mRotation(0.0f, 0.0f, 0.0f)
	{
		mProgram = 0;
		mTexture = 0;
	}


	Sprite::~Sprite()
	{
		glDeleteProgram(mProgram);
		glDeleteVertexArrays(1, &mVao);
		unloadTexure();
	}


	void Sprite::loadShaders()
	{
		GLuint shaders[2];
		shaders[0] = Shader::loadShader(String(gDefaultPathShaders) + "sprite-vert.glsl", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(String(gDefaultPathShaders) + "sprite-frag.glsl", GL_FRAGMENT_SHADER);

		mProgram = Shader::linkFromShaders(shaders, 2);

		glUseProgram(mProgram);
		setSubRect({0,0,1,1});
		glUseProgram(0);
	}


	void Sprite::setSubRect(const Rect2f &subRect) const
	{
		GLuint loc = glGetUniformLocation(mProgram, "subBottomLeft");
		glUniform2f(loc, subRect.x, subRect.y);
		loc = glGetUniformLocation(mProgram, "subSize");
		glUniform2f(loc, subRect.width, subRect.height);
	}


	void Sprite::initWithImage(const Image &image)
	{
		mImage = &image;

		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, image.getWidth(), image.getHeight());

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(),
						GL_RGBA, GL_UNSIGNED_BYTE, &image.getImageData()[0]);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		GLuint vbo;
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
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		loadShaders();

		glBindVertexArray(0);
	}


	void Sprite::renderWithoutBinding(const OpenGLWindow &window) const
	{
		//TODO This method does way too much on the CPU. Consider moving it to the GPU if it would increase performance
		//Also consider eliminating logic here

		//calculate an offset so the sprite is drawn in the upper left corner of the window by default
		Vec3f offset(	-(window.getWidth() / 2.0f),
						(window.getHeight() / 2.0f) - (mImage->getHeight()), 0.0f);

		offset += mScreenPos;
		offset /= Vec3f(window.getWidth(), window.getHeight(), 1.0f);

		//upload the transformation
		{
			Mat4 transformation(1.0f);

			//translate
			transformation *= glm::translate(offset);

			//scale
			float sx = (float)mImage->getWidth() / window.getWidth() * 2.0f * mScale.x;
			float sy = (float)mImage->getHeight() / window.getHeight() * 2.0f * mScale.y;
			Vec3f actualScale(sx, sy, mScale.z);
			transformation *= glm::scale(transformation, actualScale);

			//rotation
			Mat4 rotation(1.0f);
			rotation = glm::rotate(rotation, mRotation.x, Vec3f(1, 0, 0));
			rotation = glm::rotate(rotation, mRotation.y, Vec3f(0, 1, 0));
			rotation = glm::rotate(rotation, mRotation.z, Vec3f(0, 0, 1));
			transformation *= rotation;

			//TODO prequery the locations
			GLuint loc = glGetUniformLocation(mProgram, "transformation");
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transformation));
		}

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
	}


	void Sprite::bindForRender() const
	{
		glUseProgram(mProgram);
		glBindVertexArray(mVao);
	}


	void Sprite::unbindAfterRender() const
	{
		glBindVertexArray(0);
		glUseProgram(0);
	}


	void Sprite::render(const OpenGLWindow &window) const
	{
		bindForRender();
		renderWithoutBinding(window);
		unbindAfterRender();
	}


	void Sprite::renderSubRect(const OpenGLWindow &window, const Rect2f &subRect) const
	{
		bindForRender();
		setSubRect(subRect);
		renderWithoutBinding(window);
		unbindAfterRender();
	}


	void Sprite::unloadTexure() const
	{
		glDeleteTextures(1, &mTexture);
	}
};