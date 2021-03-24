//==================================================================================================================|
// Created 2015.01.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_MaterialData_h
#define _t3d_core_MaterialData_h

#include "MeshPrivate.h"

namespace t3d::asset
{

class mesh_p::MaterialData : protected core::OpenGLFunctions
{
  public: // TODO massive
    ~MaterialData() { qDebug() << "Destroying MaterialData instance"; }

    QString mName;
    QString mFilepath;

    unique<QOpenGLTexture> mTexture;

    void uploadMaterialData(const QString &containingDirectory);
    void bind();
    void release();
};

}

#endif
