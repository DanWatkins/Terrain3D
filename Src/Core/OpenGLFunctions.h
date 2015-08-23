//==================================================================================================================|
// Created 2014.10.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_OpenGLFunctions_H
#define _t3d_core_OpenGLFunctions_H

#include <Library.h>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtOpenGLExtensions/QOpenGLExtensions>


using BaseOpenGLFunctions = QOpenGLFunctions_4_1_Core;

namespace t3d { namespace core
{
	/*
	 * Inherit from this class protectedly to access all of the standard OpenGL functions. Call
	 * OpenGLFunctions::initializeOpenGLFunctions() before using any of the actual OpenGL functions such as glEnable().
	 */
	class OpenGLFunctions : public BaseOpenGLFunctions
	{
	public:
        bool initializeOpenGLFunctions() override;

		void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
		{
			mGL_textureStorage.glTexStorage1D(target, levels, internalformat, width);
		}

		void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
		{
			mGL_textureStorage.glTexStorage2D(target, levels, internalformat, width, height);
		}

		void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
		{
			mGL_textureStorage.glTexStorage3D(target, levels, internalformat, width, height, depth);
		}

	private:
		QOpenGLExtension_ARB_texture_storage mGL_textureStorage;
	};
}}

#endif
