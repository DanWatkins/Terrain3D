#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <fcntl.h>
#include <algorithm>

#include <fstream>
#include <istream>
#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <deque>

#include <thread>
#include <future>
#include <functional>

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <QtCore/QVector>
#include <QtGui/QtGui>
#include <QtQuick\qsgsimpletexturenode.h>
#include <QtQuick/QQuickWindow>
#include <QtCore/QMutex>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_2_Core>
#include <QtGui/QOpenGLTexture>
#include <QtConcurrent\qtconcurrentrun.h>

namespace t3d { namespace core
{
	using BaseOpenGLFunctions =  QOpenGLFunctions_4_2_Core;
}}

#define WIN32_LEAN_AND_MEAN 1

//GLM Includes
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	#include <glm/glm.hpp>
	#include <glm/ext.hpp>
#pragma GCC diagnostic pop

//typedef common types
typedef long long			int64;
typedef unsigned long long	uint64;


typedef glm::vec2			Vec2f;
typedef glm::vec3			Vec3f;
typedef glm::vec4			Vec4f;

typedef glm::i32vec2		Vec2i;
typedef glm::i32vec3		Vec3i;
typedef glm::i32vec4		Vec4i;

typedef glm::bvec1			Vec1b;
typedef glm::bvec2			Vec2b;
typedef glm::bvec3			Vec3b;
typedef glm::bvec4			Vec4b;

typedef glm::mat2			Mat2;
typedef glm::mat3			Mat3;
typedef glm::mat4			Mat4;

struct Color { float r, g, b, a; };

#include <memory>

template <typename T>
using strong = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using unique = std::unique_ptr<T>;

template<typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

//Project Includes
#include <Constants.h>
#include <Core/Helper.h>
#include <ValpineBase/Property.h>

template <typename T>
using Property = ValpineBase::Property<T>;

#endif
