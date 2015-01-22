//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "SubMesh.h"

namespace t3d { namespace Asset
{
	void mesh_p::SubMesh::uploadData()
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


	void mesh_p::SubMesh::uploadIndexData()
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
					indexBuffer.append(mesh_p::PrimitiveRestartIndex);

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


	void mesh_p::SubMesh::uploadVertexData()
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


	void mesh_p::SubMesh::render()
	{
		glBindVertexArray(mVao);
		{
			glLineWidth(1.0f);
					
			glDrawElements(GL_TRIANGLE_FAN, mIndexCount, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
	}


	void mesh_p::SubMesh::checkForErrors(const FaceData *faceData, QString &error)
	{
		if (mFaces.count() == 0)
		{
			error = QString("No faces defined for SubMesh using material ") + mMaterial;
			return;
		}

		for (int fi=0; fi<mFaces.count(); fi++)
		{
			Face &f = mFaces[fi];

			if (f.vertexIndex.count() != f.normalIndex.count()  ||  f.vertexIndex.count() != f.textureIndex.count())
			{
				error = QString("Inconsistent vertex attributes for face %1").arg(fi);
				break;
			}

			for (int i : f.vertexIndex)
			{
				if ((faceData->mVertecies.count() > i) == false)
					error = QString("Vertex position attribute out of range for face %1").arg(fi);
			}

			for (int i : f.normalIndex)
			{
				if ((faceData->mVertexNormals.count() > i) == false)
					error = QString("Vertex normal attribute out of range for face %1").arg(fi);
			}

			for (int i : f.textureIndex)
			{
				if ((faceData->mTextureCoordinates.count() > i) == false)
					error = QString("Texture coordinate attribute out of range for face %1").arg(fi);
			}

			if (!error.isEmpty())
				break;
		}
	}
}}