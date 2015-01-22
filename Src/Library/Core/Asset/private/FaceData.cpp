//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "FaceData.h"

namespace t3d { namespace Asset
{
	void Mesh::MeshPrivate::FaceData::uploadData()
	{
		initializeOpenGLFunctions();

		uploadBufferAttribute(GL_TEXTURE2, mVertecies, bufferVertexPositions);
		uploadBufferAttribute(GL_TEXTURE3, mVertexNormals, bufferVertexNormals);
		uploadBufferAttribute(GL_TEXTURE4, mTextureCoordinates, bufferTextureCoordinates);
	}


	void Mesh::MeshPrivate::FaceData::bind()
	{
		glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_BUFFER, bufferVertexPositions);
		glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_BUFFER, bufferVertexNormals);
		glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_BUFFER, bufferTextureCoordinates);	
	}


	void Mesh::MeshPrivate::FaceData::uploadBufferAttribute(GLenum textureUnit, const QVector<Mesh::MeshPrivate::Vertex> &data, GLuint &textureName)
	{
		glActiveTexture(textureUnit);
		glGenTextures(1, &textureName);
		glBindTexture(GL_TEXTURE_BUFFER, textureName);
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_TEXTURE_BUFFER, buffer);
			{
				glBufferData(GL_TEXTURE_BUFFER, data.count()*3*sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
				glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer);
			}
		}
	}
}}