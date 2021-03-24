//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_QUICK_ITEMS_CAMERA_H
#define _t3d_QUICK_ITEMS_CAMERA_H

#include <QtQuick/QQuickFramebufferObject>
#include <Terrain3D/World/Camera.h>

namespace t3d::QuickItems
{

class CameraItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY isLoadedChanged)
    Q_PROPERTY(bool isFrozen READ isFrozen WRITE setIsFrozen)

public:
    CameraItem();

    // properties
    bool isLoaded() const { return mCamera.get() != nullptr; }
    bool isFrozen() const { return mIsFrozen; }
    void setIsFrozen(bool isFrozen) { mIsFrozen = isFrozen; }

    weak<world::Camera> createCamera();
    weak<world::Camera> camera() { return mCamera; }
    void cleanup();

private:
    bool mIsFrozen;
    bool mIsSynced = false;
    strong<world::Camera> mCamera;

signals:
    void isLoadedChanged();

public:
    QQuickFramebufferObject::Renderer *createRenderer() const;
};

}

#endif
