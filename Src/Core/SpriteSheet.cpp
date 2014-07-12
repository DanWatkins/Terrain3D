//==================================================================================================================|
// Created 2014.06.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "SpriteSheet.h"

namespace t3d
{
	SpriteSheet::SpriteSheet()
	{
		mNumberOfFramesX = 1;
		mNumberOfFramesY = 1;
	}


	void SpriteSheet::init(const Image &image, unsigned numberOfFramesX, unsigned numberOfFramesY)
	{
		Sprite::init(image);
		setNumberOfFrames(numberOfFramesX, numberOfFramesY);
	}


	void SpriteSheet::setNumberOfFrames(unsigned numberOfFramesX, unsigned numberOfFramesY)
	{
		numberOfFramesX = std::max(1U, numberOfFramesX);
		numberOfFramesY = std::max(1U, numberOfFramesY);

		mNumberOfFramesX = numberOfFramesX;
		mNumberOfFramesY = numberOfFramesY;
		mFrameSize.x = getImage()->getWidth() / (float)numberOfFramesX;
		mFrameSize.y = getImage()->getHeight() / (float)numberOfFramesY;
	}


	void SpriteSheet::drawFrame(const OpenGLWindow &window, unsigned frameIndex)
	{
		Rect2f subRect;
		subRect.x = (frameIndex % mNumberOfFramesX) * mFrameSize.x;
		subRect.y = mFrameSize.y - ((frameIndex / mNumberOfFramesY) * mFrameSize.y);
		subRect.width = mFrameSize.x;
		subRect.height = mFrameSize.y;

		drawSubRect(window, subRect);
	}
};