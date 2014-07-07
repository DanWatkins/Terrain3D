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

		struct UniformLocations
		{
			GLuint subBottomLeft;
			GLuint subSize;
			GLuint transformation;
		} mUniformLocations;

		Vec3f mScreenPos;
		Vec3f mScale;
		Vec3f mRotation;
		const Image *mImage;	//TODO we only store a pointer to access the width/height. Maybe just store them?

		/**
		 * Compiles and links the necessary shaders for drawing the sprite. Uploads uniform data.
		 */
		void loadShaders();

		/**
		 * Renders the sprite without binding or unbinding any states.
		 *
		 * @param window Where the sprite should be rendered.
		 */
		void renderWithoutBinding(const OpenGLWindow &window) const;

		/**
		 * Binds the appropriate states for rendering.
		 */
		void bindForRender() const;

		/**
		 * Unbinds the states used for rendering.
		 */
		void unbindAfterRender() const;

	public:
		Sprite();

		/**
		 * Properly deletes OpenGL objects.
		 */
		~Sprite();

		/**
		 * Creates various OpenGL objects and uploads the image to the GPU for textured drawing. Also creates and
		 * uploads vertex data that represents two triangles where the texture is mapped.
		 *
		 * @param image Image data used for the texture.
		 */
		void initWithImage(const Image &image);


		/**
		 * Sets the render boundaries of the source image to be rendered. This boundary is uploaded to a uniform on
		 * the GPU.
		 * TODO decide what coordinate system is used here
		 *
		 * @param subRect The render boundaries of the source image.
		 */
		void setSubRect(const Rect2f &subRect) const;

		/**
		 * TODO establish the difference between RENDER and DRAW
		 * Draws the sprite on the specified window. All necessary bindings and unbindings are performed internally.
		 *
		 * @param window OpenGLWindow to draw the sprite on.
		 */
		void render(const OpenGLWindow &window) const;

		/**
		 * Draws the sprite on the specified window using the specified sub rectangle. No bindings are performed.
		 *
		 * @param window OpenGLWindow to draw the sprite on.
		 * @param subRect The render boundaries of the source image.
		 */
		void renderSubRect(const OpenGLWindow &window, const Rect2f &subRect) const;

		/**
		 * Returns a constant reference to the internal image used for rendering.
		 */
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

