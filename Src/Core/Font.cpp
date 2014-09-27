//==================================================================================================================|
// Created 2014.06.14 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Font.h"

namespace t3d
{
	Font::Font()
	{
		memset(&mWidths, 0, sizeof(mWidths));
	}


	bool Font::load(const String &fontname, const String &containingDirectoryPath)
	{
		unsigned char buffer[512];

		std::ifstream file;
		file.open((containingDirectoryPath + "/" + fontname + ".dat").c_str(), std::ios::binary);

		if (!file.is_open())
			return false;

		file.read((char*)&buffer, 512);

		if (file.bad())
			return false;

		//convert from raw data to width data
		for (int n=0; n<256; n++)
			mWidths[n] = (int)buffer[n*2];

		//load the image
		mImage.loadFromFile_PNG((containingDirectoryPath + "/" + fontname + ".png"));
		mSpriteSheet.init(mImage, 16, 16);

		return true;
	}


	void Font::print(const OpenGLWindow &window, const String &text, const Vec2f &pos)
	{
		float x = pos.x;
		float y = pos.y;

		if (text.size() > 0)
		{
			char firstChar = text[0];
			x -= (mSpriteSheet.getFrameSize().x - mWidths[firstChar]) / 2.0f;

			for (unsigned n=0; n<text.size(); ++n)
			{
				unsigned frame = text[n];
				mSpriteSheet.drawFrame(window, 0);
				x += static_cast<float>(mWidths[frame]);
			}
		}
	}
};