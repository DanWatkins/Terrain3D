//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Core_Asset_Mesh_H
#define _t3d_Core_Asset_Mesh_H

#include <Terrain3D/Core/OpenGLFunctions.h>
#include <Terrain3D/Library.h>

namespace t3d
{
namespace asset
{

class Manager;

class Mesh
{
  private:
    struct BoundingSphere
    {
        float radius;
        Vec3f offset;
    };

  public:
    friend class Manager;
    Mesh();

    bool init(Manager *manager, const QString &filepath);
    void queueRender(const Mat4 &totalMatrix);

    QString name() const;
    BoundingSphere &boundingSphere() { return mBoundingSphere; }
    const BoundingSphere &boundingSphere() const { return mBoundingSphere; }

    class MeshPrivate;

  private:
    strong<MeshPrivate> mPrivate;
    Manager *mManager = nullptr;
    void batchRender(const QVector<Mat4> &matricies);

    BoundingSphere mBoundingSphere;
};

}
}

#endif
