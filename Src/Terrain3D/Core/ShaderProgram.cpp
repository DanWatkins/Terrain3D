//==================================================================================================================|
// Created 2015.03.17 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ShaderProgram.h"

namespace t3d
{
namespace core
{

void ShaderProgram::init()
{
    initializeOpenGLFunctions();
    loadShaders();
}

void ShaderProgram::addShader(const QString &filename, QOpenGLShader::ShaderType shaderType)
{
    QOpenGLShader *shader = new QOpenGLShader(shaderType, mProgram.get());
    if (!shader->compileSourceFile(gDefaultPathShaders + filename))
        qDebug() << "Error compiling shader " << filename << " of type "
                 << static_cast<int>(shaderType);

    if (!mProgram->addShader(shader))
        qDebug() << "Error adding shader " << filename << " of type "
                 << static_cast<int>(shaderType);
}

void ShaderProgram::loadShaders()
{
    mProgram = makeUnique<QOpenGLShaderProgram>();
    addShaders();

    if (mProgram->link() == false)
        qFatal("Problem linking shaders");
    else
        qDebug() << "Initialized shaders";

    mProgram->bind();
    queryUniformLocations();
    refreshUniformValues();
    flushQueuedUniformValueChanges();
    mProgram->release();
}

bool ShaderProgram::bind()
{
    if (!mProgram->bind())
    {
        System::warn("Unable to bind OpenGL ShaderProgram");
        return false;
    }

    flushQueuedUniformValueChanges();

    return true;
}

void ShaderProgram::reloadShaders()
{
    loadShaders();
}

void ShaderProgram::enqueueUniformValueChange(const GLint *uniformLocation, QVariant value)
{
    if (mProgram && mProgram->isLinked())
    {
        mProgram->bind();
        setUniformFromQVariant(*uniformLocation, value);
        mProgram->release(); // TODO this can cause issues if used while the program was bound
                             // externally
    }
    else
        mQueuedUniformValueChanges.append(QPair<const GLint *, QVariant>(uniformLocation, value));
}

void ShaderProgram::setUniformFromQVariant(GLint location, QVariant &value)
{
    switch (static_cast<QMetaType::Type>(value.type()))
    {
    case QMetaType::Int:
        mProgram->setUniformValue(location, static_cast<GLint>(value.toInt()));
        break;
    case QMetaType::Double:
        mProgram->setUniformValue(location, static_cast<GLfloat>(value.toDouble()));
        break;
    case QMetaType::Float:
        mProgram->setUniformValue(location, static_cast<GLfloat>(value.toFloat()));
        break;
    default:
        qFatal("Trying to set a queued shader uniform value for an unknown type");
        // TODO this is all we support. Eventuall QOpenGLShaderProgram should support
        // setUniformValue directly from a QVariant.
    }
}

void ShaderProgram::flushQueuedUniformValueChanges()
{
    for (auto pair : mQueuedUniformValueChanges)
    {
        setUniformFromQVariant(*pair.first, pair.second);
    }

    mQueuedUniformValueChanges.clear();
}

}
}
