//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Camera_H
#define _t3d_World_Camera_H

#include <ValpineBase/Loadable.h>
#include <ValpineBase/Property.h>

#include <Terrain3D/Library.h>
#include <Terrain3D/World/Environment.h>

#include <Terrain3D/World/Terrain/Data.h>
#include <Terrain3D/World/Terrain/Renderer.h>
#include <Terrain3D/World/Entity/Renderer.h>

namespace t3d::world {

/**
     * Represents an all-in-one World instance visualizer. It can move forward/backward and left/right. It can also
     * rotate up/down and left/right.
     */
class Camera : public QObject, protected core::OpenGLFunctions, public vbase::Loadable
{
    Q_OBJECT

public slots:
    /**
     * @brief Renders everything visible by the camera using the current
     * OpenGL context.
     */
    void render();

signals:
    void finishedRendering();
    void posChanged();
    void orientationChanged();

public:
    Camera();
    ~Camera() {}

    /**
     * @brief Gets the instance ready for rendering.
     * @param configuration Contains various configuration information
     */
    void init();

    void refresh();

    /**
     * Does the heavy lifting loading. Loads large resources from file and uploads data to the GPU.
     * Must be called after init.
     */
    void prepareForRendering();

    /**
     * @brief Deallocates all memory allocated in OpenGL on the GPU.
     */
    void cleanup();

    /**
     * @brief Adjusts the aspect ratio according to \p windowWidth and \p windowHeight
     */
    void resize(unsigned windowWidth, unsigned windowHeight);

    void reloadShaders();

    void setEnvironment(Environment *environment) { mEnvironment = environment; }

    float fieldOfView() const { return mFieldOfView; }

    void setFieldOfView(float fieldOfView) { mFieldOfView = fieldOfView; }

    float nearPlane() const { return mNearPlane; }

    float farPlane() const { return mFarPlane; }

    float aspectRatio() const { return mAspectRatio; }

    float maxVerticalAngle() const { return mMaxVerticalAngle; }

    Vec3f const & pos() const { return mPos; }

    void setPosX(float x)
    {
        mPos.x = x;
        emit posChanged();
    }

    void setPosY(float y)
    {
        mPos.y = y;
        emit posChanged();
    }

    void setPosZ(float z)
    {
        mPos.z = z;
        emit posChanged();
    }

    void addPos(const Vec3f &pos)
    {
        mPos += pos;
        emit posChanged();
    }

    Vec2f const & orientationAngle() const { return mOrientationAngle; }

    void setOrientationAngle(const Vec2f &angle)
    {
        mOrientationAngle = angle;
        normalizeAngles();
        emit orientationChanged();
    }

    void addOrientationAngle(const Vec2f &angle)
    {
        mOrientationAngle += angle;
        normalizeAngles();
        emit orientationChanged();
    }

    Mat4 orientaion() const;

    void lookAt(Vec3f position);
    Vec3f forward() const;
    Vec3f right() const;
    Vec3f up() const;

    void setMode(terrain::Mode mode) { mTerrainRenderer.setMode(mode); }
    terrain::Mode mode() { return mTerrainRenderer.mode(); }

    terrain::Renderer& terrainRenderer() { return mTerrainRenderer; }

private:
    Environment *mEnvironment;
    terrain::Renderer mTerrainRenderer;
    entity::Renderer mEntityRenderer;

    float mFieldOfView = 50.0f;
    float mNearPlane = 1.0f;
    float mFarPlane = 1200.0f;
    float mAspectRatio = 1.0;
    float mMaxVerticalAngle = 90.0f;
    Vec3f mPos = Vec3f(0.0f, 25.0f, 75.0f);
    Vec2f mOrientationAngle = Vec2f(0.0f, 0.0f);

    Mat4 totalMatrix() const;
    Mat4 perspectiveMatrix() const;
    Mat4 viewMatrix() const;
    void normalizeAngles();
};

}

#endif
