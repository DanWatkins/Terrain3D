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

		void bind() { flushQueuedUniformValueChanges(); }
		void release() { mProgram->release(); }

		/**
		 * Allows uniform values to be set even if the program is not linked yet by queueing the change into a buffer
		 * that is flushed the next time the shader is bound or linked. If the shader is currently linked, then the
		 * changes will take effect immediately.
		 *
		 * \param uniformLocation A pointer to where the location value is stored. It must hold a valid location by
		 * the time the shader is linked.
		 */
		void enqueueUniformValueChange(const GLint *uniformLocation, QVariant &&value);

		/**
		 * A time for shaders to be added before linkage.
		 */
		virtual void addShaders() = 0;

		/**
		 * A time to query uniform locations and assign any value to them.
		 */
		virtual void queryUniformLocations() = 0;

		/**
		 * @returns a reference to the internal QOpenGLShaderProgram.
		 */
		QOpenGLShaderProgram& raw() { return *mProgram.get(); }

	private:
		void setUniformFromQVariant(GLint location, QVariant &value);
		void flushQueuedUniformValueChanges();

		unique<QOpenGLShaderProgram> mProgram;
		QList<QPair<const GLint*, QVariant>> mQueuedUniformValueChanges;
	};
}}

#endif
