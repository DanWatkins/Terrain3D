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

		Vec4f mPos;
		Vec4f mScale;
		const Image *mImage;	//TODO we only store a pointer to access the width/height. Maybe just store them?

		void loadShaders();
		void unloadTexure() const;

	public:
		Sprite();
		~Sprite();

		void initWithImage(const Image &image);
		void render(const OpenGLWindow &window) const;

		void setPos(Vec2f pos) { mPos.x = pos.x; mPos.y = pos.y; }
		void addPos(Vec2f pos) { mPos.x += pos.x; mPos.y += pos.y; }

		void setScale(Vec2f scale) { mScale.x = scale.x; mScale.y = scale.y; }
		void addScale(Vec2f scale) { mScale.x += scale.x; mScale.y += scale.y; }
	};
};

#endif

