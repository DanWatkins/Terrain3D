//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _SHADER_H
#define _SHADER_H

#include "Core.h"

namespace t3d
{
	namespace Shader
	{
		GLuint loadShader(const String &filename, GLenum shaderType);
		GLuint linkFromShaders(const GLuint *shaders, int shaderCount);
	};
};

#endif

