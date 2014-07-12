//==================================================================================================================|
// Created 2014.06.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SPRITE_SHEET
#define _t3d_SPRITE_SHEET

#include "Sprite.h"

namespace t3d
{
	/**
	 * \brief A specialized sprite that can draw regular sized sub-rects easily.
	 */
	//TODO it would be better to have a RawSprite base class that Sprite and SpriteSheet both inherit
	class SpriteSheet : public Sprite
	{
	private:
		int mNumberOfFramesX, mNumberOfFramesY;
		Vec2f mFrameSize;

	public:
		/**
		 * Default constructor
		 */
		SpriteSheet();

		/**
		 * Tells the sprite to use the specified image and configures the size used for frames.
		 *
		 * \param image The image data to use. This data must persist externally as a pointer is stored.
		 * \param numberOfFramesX The number of frames to split the sprite into horizontally.
		 * \param numberOfFramesY The number of frames to split the sprite into vertically.
		 */
		void init(const Image &image, unsigned numberOfFramesX, unsigned numberOfFramesY);

		/**
		 * Configures the size used for frames.
		 *
		 * \param numberOfFramesX The number of frames to split the sprite into horizontally.
		 * \param numberOfFramesY The number of frames to split the sprite into vertically.
		 */
		void setNumberOfFrames(unsigned numberOfFramesX, unsigned numberOfFramesY);

		/**
		 * Draws the specified frame index onto the window. The first frame starts with index 0 and is the
		 * upper-left section of the image. All frames drawn are shifted over appropriately so they a drawn
		 * starting at (0,0) relative to the overall position.
		 *
		 * \param window The window to draw to.
		 * \param frameIndex The index of the frame of the entire image to draw.
		 */
		void drawFrame(const OpenGLWindow &window, unsigned frameIndex);
	};
};

#endif

