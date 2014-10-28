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
	class Shader : protected OpenGLFunctions
	{
	public:
		/**
		 * Creates and compiles an OpenGL shader object.
		 *
		 * \param filepath The path to the source file
		 * \param shaderType The type of OpenGL shader to create
		 */
		GLuint loadShader(const String &filepath, GLenum shaderType);

		/**
		 * Links the shader objects to a new OpenGL program object. The old shader objects are deleted.
		 *
		 * \param shaders Array of shader objects to link
		 * \param shaderCount Number of elements in the shaders array
		 *
		 * \returns The new OpenGL program object
		 */
		GLuint linkFromShaders(const GLuint *shaders, int shaderCount);
	};
};

#endif

