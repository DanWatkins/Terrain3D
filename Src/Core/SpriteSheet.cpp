//==================================================================================================================|
// Created 2014.06.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "SpriteSheet.h"

namespace t3d
{
	void SpriteSheet::init(const Image &image, int numberOfFramesX, int numberOfFramesY)
	{
		mSprite.initWithImage(image);
		setNumberOfFrames(numberOfFramesX, numberOfFramesY);
	}


	void SpriteSheet::setNumberOfFrames(int numberOfFramesX, int numberOfFramesY)
	{
		mNumberOfFramesX = numberOfFramesX;
		mNumberOfFramesY = numberOfFramesY;
		mFrameSize.x = mSprite.getImage()->getWidth() / (float)numberOfFramesX;
		mFrameSize.y = mSprite.getImage()->getHeight() / (float)numberOfFramesY;
	}


	void SpriteSheet::render(const OpenGLWindow &window, int frameIndex)
	{
		Rect2f subRect;
		subRect.x = (frameIndex % mNumberOfFramesX) * mFrameSize.x;
		subRect.y = mFrameSize.y - ((frameIndex / mNumberOfFramesY) * mFrameSize.y);
		subRect.width = mFrameSize.x;
		subRect.height = mFrameSize.y;
		mSprite.drawSubRect(window, subRect);
	}
};