//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Camera.h"

namespace t3d { namespace world {

Camera::Camera()
{
    mOrientationAngle = Vec2f(2.3 * glm::pi<float>() / 3, 0.5f);
}

void Camera::init()
{
    vbase::Loadable::Begin b(this);
    initializeOpenGLFunctions();

    mTerrainRenderer.init(&mEnvironment->terrainData());
    mEntityRenderer.setManager(&mEnvironment->entityManager());
}

void Camera::refresh()
{
    vbase::Loadable::Begin b(this);
    mTerrainRenderer.refresh();
}

void Camera::prepareForRendering()
{
    mTerrainRenderer.prepareForRendering();
}

void Camera::cleanup()
{
    mTerrainRenderer.cleanup();
}

void Camera::render()
{
    if (pIsLoading)
    {
        qWarning("Trying to render Camera while loading...rendering canceled.");
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glClearColor(1.0f, 0.9f, 0.8f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    mTerrainRenderer.render(mPos, viewMatrix(), perspectiveMatrix());

    mEntityRenderer.renderAll(totalMatrix());
    mEnvironment->assetManager().renderAllQueued();

    emit finishedRendering();
}

void Camera::resize(unsigned windowWidth, unsigned windowHeight)
{
    mAspectRatio = (float)windowWidth / (float)windowHeight;
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
}

void Camera::reloadShaders()
{
    vbase::Loadable::Begin b(this);
    mTerrainRenderer.reloadShaders();
}

Mat4 Camera::orientaion() const
{
    Mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, mOrientationAngle.y, Vec3f(1, 0, 0));
    orientation = glm::rotate(orientation, mOrientationAngle.x, Vec3f(0, 1, 0));
    return orientation;
}

void Camera::lookAt(Vec3f position)
{
    if (mPos == position)
    {
        std::cout << "MEGA ERROR: You are trying to look at your origin" << std::endl;
        return;
    }

    Vec3f direction = glm::normalize(position - mPos);
    mOrientationAngle.y = asinf(-direction.y);
    mOrientationAngle.x = -atan2f(-direction.x, -direction.z);
    normalizeAngles();
}

Vec3f Camera::forward() const
{
    return Vec3f(glm::inverse(orientaion()) * Vec4f(0, 0, -1, 1));
}

Vec3f Camera::right() const
{
    return Vec3f(glm::inverse(orientaion()) * Vec4f(1, 0, 0, 1));
}

Vec3f Camera::up() const
{
    return Vec3f(glm::inverse(orientaion()) * Vec4f(0, 1, 0, 1));
}

Mat4 Camera::totalMatrix() const
{
    return perspectiveMatrix() * viewMatrix();
}

Mat4 Camera::perspectiveMatrix() const
{
    return glm::perspective<float>(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
}

Mat4 Camera::viewMatrix() const
{
    return orientaion() * glm::translate(Mat4(1.0f), -mPos);
}

void Camera::normalizeAngles()
{
    mOrientationAngle.x = fmodf(mOrientationAngle.x, glm::pi<float>() * 2.0f);

    if (mOrientationAngle.x < 0.0f)
        mOrientationAngle.x += glm::pi<float>() * 2.0f;

    if (mOrientationAngle.y > mMaxVerticalAngle)
        mOrientationAngle.y = mMaxVerticalAngle;
    else if (mOrientationAngle.y < -mMaxVerticalAngle)
        mOrientationAngle.y = -mMaxVerticalAngle;
}

}}
