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

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <QtCore/QVector>
#include <QtGui/QtGui>
#include <Core/OpenGLFunctions.h>

#define WIN32_LEAN_AND_MEAN 1

//GLM Includes
#pragma warning(push)
#pragma warning(disable:4201)
#pragma warning(disable:4996)
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	#include <glm/glm.hpp>
	#include <glm/ext.hpp>
//#pragma GCC diagnostic pop
#pragma warning(pop)

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

//Project Includes
#include <Constants.h>
#include <Core/Helper.h>

#endif // MAIN_H
