#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS 1

#include <algorithm>
#include <fcntl.h>
#include <iostream>

#include <fstream>
#include <istream>
#include <sstream>
#include <string>

#include <deque>
#include <list>
#include <vector>

#include <functional>
#include <future>
#include <thread>

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QVector>
#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QtGui>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>

#define WIN32_LEAN_AND_MEAN 1

// GLM Includes
#pragma GCC system_header
#pragma clang system_header

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#pragma GCC diagnostic pop
#pragma Clang diagnostic pop

// typedef common types
typedef long long int64;
typedef unsigned long long uint64;

// TODO move all this into ValpineBase
// Like ValpineBase/MathTypes.h
typedef glm::vec2 Vec2f;
typedef glm::vec3 Vec3f;
typedef glm::vec4 Vec4f;

typedef glm::i32vec2 Vec2i;
typedef glm::i32vec3 Vec3i;
typedef glm::i32vec4 Vec4i;

typedef glm::bvec1 Vec1b;
typedef glm::bvec2 Vec2b;
typedef glm::bvec3 Vec3b;
typedef glm::bvec4 Vec4b;

typedef glm::mat2 Mat2;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

struct Color
{
    float r, g, b, a;
};

#include <memory>

template <typename T> using strong = std::shared_ptr<T>;

template <typename T> using weak = std::weak_ptr<T>;

template <typename T> using unique = std::unique_ptr<T>;

template <typename T, typename... Args> std::unique_ptr<T> makeUnique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Project Includes
#include <Terrain3D/Constants.h>
#include <Terrain3D/Core/OpenGLFunctions.h>

#include <ValpineBase/Helper.h>
#include <ValpineBase/System.h>

using System = vbase::System;

#endif
