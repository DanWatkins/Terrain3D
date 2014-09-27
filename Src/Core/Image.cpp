//==================================================================================================================|
// Created 2014.06.01 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Image.h"
#include <lodepng.h>

namespace t3d
{
	bool Image::loadFromFile_PNG(const String &filepath)
	{
		ImageData png;
		ImageData data; //the raw pixels
		lodepng::State state;

		lodepng::load_file(png, filepath.c_str()); //load the image file with given filename
		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...,
		//use it as texture, draw it, ...
		//State state contains extra information about the PNG such as text chunks, ...

		unsigned error = lodepng::decode(data, mWidth, mHeight, state, png);

		if (error)
		{
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
			return false;
		}
		else
		{
			mImageData = data;
		}

		flipVertically();

		return true;
	}

	
	void Image::flipVertically()
	{
		int width = getWidth()*4;
		int height = getHeight();
		int pos = width * height - width;

		ImageData newData;
		newData.reserve(mImageData.size());
		ImageData::iterator oldIter = mImageData.end();

		while (pos >= 0)
		{
			oldIter -= width;
			newData.insert(newData.end(), oldIter, oldIter+width);
			pos -= width;
		}

		mImageData.assign(newData.begin(), newData.end());
	}
};