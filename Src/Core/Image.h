//==================================================================================================================|
// Created 2014.06.01 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_IMAGE_H
#define _t3d_IMAGE_H

#include "../Main.h"

namespace t3d
{
	/**
	 * \brief Stores per-pixel, GL_RGBA8 image data in a contiguous memory block. Can deserialize the PNG format from file.
	 */
	//TODO it might be useful to have a validity state system. Consider encapsulating validity in a class
	//because I've needed this design pattern in a lot of places. class Validatable
	class Image
	{
	private:
		typedef std::vector<unsigned char> ImageData;
		ImageData mImageData;
		GLuint mWidth, mHeight;

		/**
		 * Flips the image about the x-axis
		 */
		void flipVertically();

	public:

		/**
		 * Deserializes a PNG format image file.
		 *
		 * \param filepath Path to the image file
		 */
		bool loadFromFile_PNG(const String &filepath);

		/**
		 * \returns Width of the image in pixels
		 */
		int getWidth() const { return mWidth; }

		/**
		 * \returns Height of the image in pixels
		 */
		int getHeight() const { return mHeight; }

		/**
		 * \returns Pointer to the internal image data.
		 */
		const ImageData& getImageData() const { return mImageData; }
	};
};

#endif


/**
 \class t3d::Image

 There is little functionality associated with an image. Its purpose is to store image data for use
 with other systems.

 Usage example:

 \code
 Image image;
 image.loadFromFile_PNG("./myImage.png");
 \endcode

 */