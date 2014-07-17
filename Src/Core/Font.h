//==================================================================================================================|
// Created 2014.06.14 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_FONT_H
#define _t3d_FONT_H

#include "../Main.h"
#include "SpriteSheet.h"

namespace t3d
{
	/**
	 * \brief Renders text
	 */
	class Font
	{
	private:
		Image mImage;
		SpriteSheet mSpriteSheet;
		int mWidths[256];
		int mVerticalOffset;

	public:
		Font();

		bool load(const String &fontname, const String &containingDirectoryPath);
		void print(const OpenGLWindow &window, const String &text, const Vec2f &pos) const;
	};
};


#endif

