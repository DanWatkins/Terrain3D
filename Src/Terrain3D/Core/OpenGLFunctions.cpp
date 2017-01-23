//==================================================================================================================|
// Created 2015.03.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLFunctions.h"

namespace t3d { namespace core {

bool OpenGLFunctions::initializeOpenGLFunctions()
{
	if (!BaseOpenGLFunctions::initializeOpenGLFunctions())
	{
        System::warn("Unable to initialize OpenGLFunctions");
		return false;
	}

	if (!mGL_textureStorage.initializeOpenGLFunctions())
	{
        System::warn("Unable to load required OpenGL extensions for OpenGLFunctions");
		return false;
	}

	return true;
}

}}
