//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "MaterialData.h"
#include <Core/Image.h>

namespace t3d
{
	void Mesh::MaterialData::uploadMaterialData(const QString &containingDirectory)
	{
		initializeOpenGLFunctions();

		Image image;
		image.loadFromFile_PNG(containingDirectory + mFilepath);
		
		int smallSize = std::min(image.getWidth(), image.getHeight());

		int levels = std::min(static_cast<int>(log(smallSize)/log(2)), 10);

		glActiveTexture(GL_TEXTURE5);
		glGenTextures(1, &mMaterial);
		glBindTexture(GL_TEXTURE_2D, mMaterial);
		{
			glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, image.getWidth(), image.getHeight());
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, &image.getImageData()[0]);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}


	void Mesh::MaterialData::bind()
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, mMaterial);
	}
}