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
	void Image::loadFromFile_PNG(String filepath)
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
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		else
			mImageData = data;
	}
};