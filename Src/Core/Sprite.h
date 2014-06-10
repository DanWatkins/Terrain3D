//==================================================================================================================|
// Created 2014.05.31 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SPRITE_H
#define _t3d_SPRITE_H

#include "../Main.h"
#include "Image.h"
#include "OpenGLWindow.h"

namespace t3d
{
	class Sprite
	{
	private:
		GLuint mProgram;
		GLuint mTexture;
		GLuint mVao;

		Vec3f mOffset;
		Vec3f mScale;
		Vec3f mRotation;
		const Image *mImage;	//TODO we only store a pointer to access the width/height. Maybe just store them?

		void loadShaders();
		void unloadTexure() const;

	public:
		Sprite();
		~Sprite();

		void initWithImage(const Image &image);
		void render(const OpenGLWindow &window) const;
		void renderSubImage(const OpenGLWindow &window, const Vec2f &subImageP1, const Vec2f &subImageP2);

		void setOffset(Vec3f offset) { mOffset = offset; }
		void addOffset(Vec3f offset) { mOffset += offset; }
		void setScale(Vec3f scale) { mScale = scale; }
		void addScale(Vec3f scale) { mScale += scale; }
		void setRotation(Vec3f rotation) { mRotation = rotation; }
		void addRotation(Vec3f rotation) { mRotation += rotation; }
	};
};

#endif

