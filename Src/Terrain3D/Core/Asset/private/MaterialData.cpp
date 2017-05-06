//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "MaterialData.h"

namespace t3d { namespace asset {

void mesh_p::MaterialData::uploadMaterialData(const QString &containingDirectory)
{
    initializeOpenGLFunctions();

    mTexture = unique<QOpenGLTexture>(new QOpenGLTexture(QImage(containingDirectory + mFilepath).mirrored()));
    mTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    mTexture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void mesh_p::MaterialData::bind()
{
    glActiveTexture(GL_TEXTURE5);
    mTexture->bind();
}

void mesh_p::MaterialData::release()
{
    mTexture->release();
}

}}
