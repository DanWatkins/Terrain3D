//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mesh.h"

namespace t3d
{
	void Mesh::SubMesh::uploadData()
	{
		initializeOpenGLFunctions();

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		{
			uploadIndexData();
			uploadVertexData();
		}
		glBindVertexArray(0);
	}


	void Mesh::SubMesh::uploadIndexData()
	{
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		{
			QVector<GLuint> indexBuffer;
			indexBuffer.reserve(mFaces.count() * 4 - 1);

			GLuint i=0;
			for (Face f : mFaces)
			{
				if (!indexBuffer.isEmpty())
					indexBuffer.append(Mesh::PrimitiveRestartIndex);

				for (int v : f.vertexIndex)
				{
					Q_UNUSED(v);
					indexBuffer.append(i++);
				}
			}

			//mIndexCount = indexBuffer.count();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.count()*sizeof(GLuint), &indexBuffer[0], GL_STATIC_DRAW);
		}
	}


	void Mesh::SubMesh::uploadVertexData()
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		{
			QVector<GLint> vertexIndicies;
			vertexIndicies.reserve(mFaces.count()*3*2);

			//add the vertex position indicies
			for (Face f : mFaces)
			{
				for (int i : f.vertexIndex)
					vertexIndicies.append(static_cast<GLint>(i));
			}

			int normalOffset = vertexIndicies.count() * sizeof(GLint);

			//add the vertex normal indicies
			for (Face f : mFaces)
			{
				for (int i : f.normalIndex)
					vertexIndicies.append(static_cast<GLint>(i));
			}

			int textureOffset = vertexIndicies.count() * sizeof(GLint);

			//add the texture coordinate indicies
			for (Face f : mFaces)
			{
				for (int i : f.textureIndex)
					vertexIndicies.append(static_cast<GLint>(i));
			}

			mIndexCount = vertexIndicies.count();

			glBufferData(GL_ARRAY_BUFFER, vertexIndicies.count()*sizeof(GLuint), &vertexIndicies[0], GL_STATIC_DRAW);
			
			glVertexAttribIPointer(0, 1, GL_INT, 0, NULL);
			glEnableVertexAttribArray(0);

			glVertexAttribIPointer(1, 1, GL_INT, 0, (void*)normalOffset);
			glEnableVertexAttribArray(1);

			glVertexAttribIPointer(2, 1, GL_INT, 0, (void*)textureOffset);
			glEnableVertexAttribArray(2);
		}
	}


	void Mesh::SubMesh::render()
	{
		glBindVertexArray(mVao);
		{
			glLineWidth(1.0f);
					
			glDrawElements(GL_TRIANGLE_FAN, mIndexCount, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
	}
}