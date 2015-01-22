//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "MaterialData.h"
#include <Core/Image.h>

namespace t3d { namespace Asset
{
	void Mesh::MaterialData::uploadMaterialData(const QString &containingDirectory)
	{
		initializeOpenGLFunctions();

		mTexture = strong<QOpenGLTexture>(new QOpenGLTexture(QImage(containingDirectory + mFilepath).mirrored()));
		mTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
		mTexture->setMagnificationFilter(QOpenGLTexture::Linear);
	}


	void Mesh::MaterialData::bind()
	{
		glActiveTexture(GL_TEXTURE5);
		mTexture->bind();
	}
}}