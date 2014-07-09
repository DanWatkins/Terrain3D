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
	/**
	 * \brief Manages the drawing and transformation of two textured quads (rectangle).
	 */
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
		 * Draws the sprite without binding or unbinding any states.
		 *
		 * @param window Where the sprite should be drawn.
		 */
		void drawWithoutBinding(const OpenGLWindow &window) const;

		/**
		 * Binds the appropriate states for drawing.
		 */
		void bindForDraw() const;

		/**
		 * Unbinds the states used for drawing.
		 */
		void unbindAfterDraw() const;

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
		 * Sets the draw boundaries of the source image to be drawn. This boundary is uploaded to a uniform on
		 * the GPU.
		 * TODO decide what coordinate system is used here
		 *
		 * @param subRect The draw boundaries of the source image.
		 */
		void setSubRect(const Rect2f &subRect) const;

		/**
		 * Draws the sprite on the specified window. All necessary bindings and unbindings are performed internally.
		 *
		 * @param window OpenGLWindow to draw the sprite on.
		 */
		void draw(const OpenGLWindow &window) const;

		/**
		 * Draws the sprite on the specified window using the specified sub rectangle. No bindings are performed.
		 *
		 * @param window OpenGLWindow to draw the sprite on.
		 * @param subRect The draw boundaries of the source image.
		 */
		void drawSubRect(const OpenGLWindow &window, const Rect2f &subRect) const;

		/**
		 * Returns a constant reference to the internal image used for drawing.
		 */
		const Image *getImage() const { return mImage; }



		/**
		 * Sets the screen position in window space
		 */
		void setScreenPos(const Vec3f &screenPos) { mScreenPos = screenPos; }

		/**
		 * @return Screen position in window space
		 */
		void addScreenPos(const Vec3f &screenPos) { mScreenPos += screenPos; }

		/**
		 * Sets the scale where each component represents the factor for each axis
		 */
		void setScale(const Vec3f &scale) { mScale = scale; }

		/**
		 * Adds a scale amount where each component represents the additional factor for each axis
		 */
		void addScale(const Vec3f &scale) { mScale += scale; }

		/**
		 * //TODO what unit are the rotations in?
		 */
		void setRotation(const Vec3f &rotation) { mRotation = rotation; }

		/**
		 * //TODO what unit are the rotations in
		 */
		void addRotation(const Vec3f &rotation) { mRotation += rotation; }
	};
};

#endif


/**
 \class t3d::Sprite

 A pointer to a valid Image object is stored internally. The image must persist for the Sprite to work.

 Basic usage example:
 \code

 Image image;
 image.loadFromFile_PNG("./smileFace.png");

 Sprite texture;
 texture.initWithImage(image);

 \endcode

 A sprite can have a sub rect set to draw only a portion of the source image.

 Sub-rect example:
 \code
 \endcode

 */