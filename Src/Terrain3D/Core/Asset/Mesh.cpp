//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mesh.h"
#include "Manager.h"

#include "./private/MeshPrivate.h"

namespace t3d::asset
{

Mesh::Mesh() : mPrivate(new MeshPrivate(this))
{
}

bool Mesh::init(Manager *manager, const QString &filepath)
{
    mManager = manager;
    return mPrivate->initWithFile(filepath);
}

void Mesh::queueRender(const Mat4 &totalMatrix)
{
    mManager->queueMeshRender(this, totalMatrix);
}

void Mesh::batchRender(const QVector<Mat4> &matricies)
{
    mPrivate->batchRender(matricies);
}

QString Mesh::name() const
{
    return mPrivate->name();
}

}
