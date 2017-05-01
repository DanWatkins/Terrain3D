//==================================================================================================================|
// Created 2014.10.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_OpenGLFunctions_H
#define _t3d_core_OpenGLFunctions_H

#include <Terrain3D/Library.h>
#include <QtGui/QOpenGLExtraFunctions>
#include <QtOpenGLExtensions/QOpenGLExtensions>

using BaseOpenGLFunctions = QOpenGLExtraFunctions;

namespace t3d { namespace core {

/*
 * Inherit from this class protectedly to access all of the standard OpenGL functions. Call
 * OpenGLFunctions::initializeOpenGLFunctions() before using any of the actual OpenGL functions such as glEnable().
 */
class OpenGLFunctions : public BaseOpenGLFunctions
{
public:
    bool initializeOpenGLFunctions();

    void glPolygonMode(GLenum face, GLenum mode)
    {
        // TODO: Not available with OpenGL ES 3.2
    }

    void glPatchParameterfv(GLenum pname, const GLfloat *values)
    {
        this->tessellationShader.glPatchParameterfv(pname, values);
    }

    void glPatchParameteri(GLenum pname, GLint value)
    {
        this->tessellationShader.glPatchParameteri(pname, value);
    }

    void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
    {
        this->textureBufferObject.glTexBufferARB(target, internalformat, buffer);
    }

    void glPrimitiveRestartIndex(GLuint index)
    {
        this->primitiveRestart.glPrimitiveRestartIndexNV(index);
    }

    void glPrimitiveRestart()
    {
        this->primitiveRestart.glPrimitiveRestartNV();
    }

private:
    QOpenGLExtension_ARB_tessellation_shader tessellationShader;
    QOpenGLExtension_ARB_texture_buffer_object textureBufferObject;
    QOpenGLExtension_NV_primitive_restart primitiveRestart;
};

}}

#endif
