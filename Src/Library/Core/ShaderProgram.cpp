//==================================================================================================================|
// Created 2015.03.17 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ShaderProgram.h"

namespace t3d { namespace core
{
	void ShaderProgram::init()
	{
		initializeOpenGLFunctions();
		loadShaders();
	}


	void ShaderProgram::addShader(const QString &filename, QOpenGLShader::ShaderType shaderType)
	{
		QOpenGLShader *shader = new QOpenGLShader(shaderType, mProgram.get());
		if (!shader->compileSourceFile(gDefaultPathShaders + "/terrain/" + filename))
			qDebug() << "Error compiling shader " << filename << " of type " << static_cast<int>(shaderType);
		
		if (!mProgram->addShader(shader))
			qDebug() << "Error adding shader " << filename << " of type " << static_cast<int>(shaderType);
	}


	void ShaderProgram::loadShaders()
	{
		mProgram = std::make_unique<QOpenGLShaderProgram>();
		addShaders();

		if (mProgram->link() == false)
			qFatal("Problem linking shaders");
		else
			qDebug() << "Initialized shaders";

		queryUniformLocations();
		updateUniformValues();
	}
}}