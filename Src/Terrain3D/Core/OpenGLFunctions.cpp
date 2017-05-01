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
    BaseOpenGLFunctions::initializeOpenGLFunctions();

    if (!this->tessellationShader.initializeOpenGLFunctions())
    {
        System::warn("Unable to initialize tesselation shader extension");
        return false;
    }

    if (!this->textureBufferObject.initializeOpenGLFunctions())
    {
        System::warn("Unable to initialize texture buffer object extension");
        return false;
    }

    if (!this->primitiveRestart.initializeOpenGLFunctions())
    {
        System::warn("Unable to initialize texture buffer object extension");
        return false;
    }

	return true;
}

}}
