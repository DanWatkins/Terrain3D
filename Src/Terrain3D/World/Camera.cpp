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

    lookAt(Vec3f(60, 20, 60));
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

    mTerrainRenderer.render(pPos, viewMatrix(), perspectiveMatrix());

    mEntityRenderer.renderAll(totalMatrix());
    mEnvironment->assetManager().renderAllQueued();

    emit finishedRendering();
}

void Camera::resize(unsigned windowWidth, unsigned windowHeight)
{
    pAspectRatio = (float)windowWidth / (float)windowHeight;
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
}

void Camera::reloadShaders()
{
    vbase::Loadable::Begin b(this);
    mTerrainRenderer.reloadShaders();
}

Mat4 Camera::orientaion() const
{
    Mat4 orientation;
    orientation = glm::rotate(orientation, pOrientationAngle().y, Vec3f(1, 0, 0));
    orientation = glm::rotate(orientation, pOrientationAngle().x, Vec3f(0, 1, 0));
    return orientation;
}

void Camera::lookAt(Vec3f position)
{
    if (pPos == position)
    {
        std::cout << "MEGA ERROR: You are trying to look at your origin" << std::endl;
        return;
    }

    Vec3f direction = glm::normalize(position - pPos);
    pOrientationAngle().y = asinf(-direction.y);
    pOrientationAngle().x = -atan2f(-direction.x, -direction.z);
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
    return glm::perspective<float>(pFieldOfView, pAspectRatio, pNearPlane, pFarPlane);
}

Mat4 Camera::viewMatrix() const
{
    return orientaion() * glm::translate(Mat4(), -pPos);
}

void Camera::normalizeAngles()
{
    pOrientationAngle().x = fmodf(pOrientationAngle().x, glm::pi<float>() * 2.0f);
    if (pOrientationAngle().x < 0.0f)
        pOrientationAngle().x += glm::pi<float>() * 2.0f;

    if (pOrientationAngle().y > pMaxVerticalAngle)
        pOrientationAngle().y = pMaxVerticalAngle;
    else if (pOrientationAngle().y < -pMaxVerticalAngle)
        pOrientationAngle().y = -pMaxVerticalAngle;
}

}}
