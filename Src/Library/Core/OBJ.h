//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_MD2_H
#define _t3d_CORE_MD2_H

#include <Main.h>
#include <Core/Image.h>
#include <Core/OpenGLFunctions.h>

namespace t3d
{
	class OBJ : protected OpenGLFunctions
	{
	public:
		OBJ();

		bool load(const QString &filepath);
		void render(const Mat4 &totalMatrix);

	private:
		struct Vertex
		{
			GLfloat values[3];
		};

		QVector<Vertex> mVertecies;
		QVector<GLuint> mIndicies;

		QOpenGLShaderProgram mProgram;
		GLuint mVao;

		const GLuint PrimitiveRestartIndex = 900000000;

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
		} mUniforms;

	private:
		bool parseField(const QStringList &field);
		void loadShaders();
		void uploadData();
	};
}

#endif

