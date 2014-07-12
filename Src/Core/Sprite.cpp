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
		glDeleteTextures(1, &mTexture);
	}


	void Sprite::loadShaders()
	{
		GLuint shaders[2];
		shaders[0] = Shader::loadShader(gDefaultPathShaders + "sprite-vert.glsl", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(gDefaultPathShaders + "sprite-frag.glsl", GL_FRAGMENT_SHADER);

		mProgram = Shader::linkFromShaders(shaders, 2);

		glUseProgram(mProgram);

		mUniformLocations.subBottomLeft = glGetUniformLocation(mProgram, "subBottomLeft");
		mUniformLocations.subSize = glGetUniformLocation(mProgram, "subSize");
		mUniformLocations.transformation = glGetUniformLocation(mProgram, "transformation");

		setSubRect({0,0,1,1});

		glUseProgram(0);
	}


	void Sprite::setSubRect(const Rect2f &subRect) const
	{
		//TODO not sure about marking something like this as const. Sure, it's not changing instance data, but it
		//is changing data in the shader
		//TODO as you can see, we have to convert to NDC here. Pretty gross
		glUniform2f(mUniformLocations.subBottomLeft, subRect.x / mImage->getWidth(), subRect.y / mImage->getHeight());
		glUniform2f(mUniformLocations.subSize, subRect.width / mImage->getWidth(), subRect.height / mImage->getHeight());
	}


	void Sprite::init(const Image &image)
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


	void Sprite::drawWithoutBinding(const OpenGLWindow &window) const
	{
		//TODO This method does way too much on the CPU. Consider moving it to the GPU if it would increase performance
		//Also consider eliminating logic here

		//calculate an offset so the sprite is drawn in the upper left corner of the window by default
		Vec3f offset(	-(window.getWidth() / 2.0f),
						(window.getHeight() / 2.0f) - (mImage->getHeight()), 0.0f);

		offset += mScreenPos;
		offset /= Vec3f(window.getWidth(), window.getHeight(), 1.0f);

		//compute and upload the transformation
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
			glUniformMatrix4fv(mUniformLocations.transformation, 1, GL_FALSE, glm::value_ptr(transformation));
		}

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
	}


	void Sprite::bindForDraw() const
	{
		glUseProgram(mProgram);
		glBindVertexArray(mVao);
	}


	void Sprite::unbindAfterDraw() const
	{
		glBindVertexArray(0);
		glUseProgram(0);
	}


	void Sprite::draw(const OpenGLWindow &window) const
	{
		bindForDraw();
		drawWithoutBinding(window);
		unbindAfterDraw();
	}


	void Sprite::drawSubRect(const OpenGLWindow &window, const Rect2f &subRect) const
	{
		bindForDraw();
		setSubRect(subRect);
		drawWithoutBinding(window);
		unbindAfterDraw();
	}
};