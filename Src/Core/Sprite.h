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

		Vec3f mScreenPos;
		Vec3f mScale;
		Vec3f mRotation;
		const Image *mImage;	//TODO we only store a pointer to access the width/height. Maybe just store them?

		void loadShaders();
		void unloadTexure() const;

		void renderWithoutBinding(const OpenGLWindow &window) const;
		void bindForRender() const;
		void unbindAfterRender() const;

	public:
		Sprite();
		~Sprite();

		void initWithImage(const Image &image);
		void setSubRect(const Rect2f &subRect) const;
		void render(const OpenGLWindow &window) const;
		void renderSubRect(const OpenGLWindow &window, const Rect2f &subRect) const;

		const Image *getImage() const { return mImage; }

		void setScreenPos(Vec3f screenPos) { mScreenPos = screenPos; }
		void addScreenPos(Vec3f screenPos) { mScreenPos += screenPos; }
		void setScale(Vec3f scale) { mScale = scale; }
		void addScale(Vec3f scale) { mScale += scale; }
		void setRotation(Vec3f rotation) { mRotation = rotation; }
		void addRotation(Vec3f rotation) { mRotation += rotation; }
	};
};

#endif

