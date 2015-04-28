//==================================================================================================================|
// Created 2014.10.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_OpenGLFunctions_H
#define _t3d_core_OpenGLFunctions_H

#include <Library.h>

#if defined(_WIN32) //We need 4_2 to use NSIGHT debugger
	#include <QtGui/QOpenGLFunctions_4_2_Core>
	using BaseOpenGLFunctions = QOpenGLFunctions_4_2_Core;

#elif defined(__APPLE__) || defined(__linux__)
	#include <QtGui/QOpenGLFunctions_4_1_Core>
	using BaseOpenGLFunctions = QOpenGLFunctions_4_1_Core;
#else
	#error Unsupported platform
#endif

namespace t3d { namespace core
{
	/*
	 * Inherit from this class protectedly to access all of the standard OpenGL functions. Call
	 * OpenGLFunctions::initializeOpenGLFunctions() before using any of the actual OpenGL functions such as glEnable().
	 */
	class OpenGLFunctions : public BaseOpenGLFunctions
	{

	};
}}

#endif
