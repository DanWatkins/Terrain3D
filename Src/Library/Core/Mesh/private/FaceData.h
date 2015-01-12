//==================================================================================================================|
// Created 2015.01.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_FACE_DATA_H
#define _t3d_CORE_FACE_DATA_H

#include "Mesh.h"

namespace t3d
{
	class Mesh::FaceData : public OpenGLFunctions
	{
	public:  //TODO massive
		QVector<Vertex> mVertecies;
		QVector<Vertex> mVertexNormals;
		QVector<Vertex> mTextureCoordinates;

		GLuint bufferVertexPositions;
		GLuint bufferVertexNormals;
		GLuint bufferTextureCoordinates;

		void uploadData();
		void bind();

	private:
		void uploadBufferAttribute(GLenum textureUnit, const QVector<Vertex> &data, GLuint &textureName);
	};
}

#endif

