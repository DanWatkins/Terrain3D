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

namespace t3d
{
	class Sprite
	{
	private:
		GLuint mProgram;
		GLuint mTexture;
		GLuint mVao;

		void loadShaders();
		void unloadTexure() const;

	public:
		Sprite();
		~Sprite();

		void initWithImage(const Image &image);
		void render() const;
	};
};

#endif

