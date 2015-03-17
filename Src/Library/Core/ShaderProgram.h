//==================================================================================================================|
// Created 2015.03.17 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Core_ShaderProgram_H
#define _t3d_Core_ShaderProgram_H

#include <Library.h>

namespace t3d { namespace core
{
	class ShaderProgram : public QObject, protected OpenGLFunctions
	{
		Q_OBJECT

	protected:
		void init();
		void addShader(const QString &filename, QOpenGLShader::ShaderType shaderType);
		void loadShaders();


		virtual void addShaders() = 0;
		virtual void queryUniformLocations() = 0;
		virtual void updateUniformValues() = 0;

		QOpenGLShaderProgram& raw() { return *mProgram.get(); }

	private:
		unique<QOpenGLShaderProgram> mProgram;
	};
}}

#endif
