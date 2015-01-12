//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mesh.h"

namespace t3d
{
	void Mesh::render(const Mat4 &totalMatrix)
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
							   glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			glBindVertexArray(mVao);
			{
				glLineWidth(1.0f);

				mFaceData.bind();
				mMaterialData.bind();
					
				glDrawElements(GL_TRIANGLE_FAN, mRenderInfo.indexCount, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);
		}
		mProgram.release();
	}


	void Mesh::init()
	{
		loadShaders();
		mProgram.bind();
		{
			mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
			mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
			mUniforms.indexCount = mProgram.uniformLocation("indexCount");

			glGenVertexArrays(1, &mVao);
			glBindVertexArray(mVao);
			{
				uploadData();

				glEnable(GL_PRIMITIVE_RESTART);
				glPrimitiveRestartIndex(PrimitiveRestartIndex);
			}
			glBindVertexArray(0);
		}
		mProgram.release();
	}

	
	void Mesh::loadShaders()
	{
		QOpenGLShader vertexShader(QOpenGLShader::Vertex, nullptr);
		vertexShader.compileSourceFile(gDefaultPathShaders + "mesh-vert.glsl");
		mProgram.addShader(&vertexShader);

		QOpenGLShader fragmentShader(QOpenGLShader::Fragment, nullptr);
		fragmentShader.compileSourceFile(gDefaultPathShaders + "mesh-frag.glsl");
		mProgram.addShader(&fragmentShader);

		if (mProgram.link() == false)
			printf("Problem linking Mesh mesh shadres\n");
		else
			printf("Initialized Mesh mesh shaders\n");
	}


	void Mesh::uploadData()
	{
		checkForErrors();

		
		mFaceData.uploadData();
		mMaterialData.uploadMaterialData(mContainingDirectory);
		uploadIndexData();
		uploadVertexData();
	}


	void Mesh::checkForErrors()
	{
		QString error;

		if (mFaces.count() == 0)
			error = QString("No faces defined");
		else if (mFaceData.mVertecies.count() == 0)
			error = QString("No vertex positions defined");
		else if (mFaceData.mVertexNormals.count() == 0)
			error = QString("No vertex normals defined");
		else if (mFaceData.mTextureCoordinates.count() == 0)
			error = QString("No texture coordinates defined");
		else
		{
			//verify every face has things for each index
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
					if ((mFaceData.mVertecies.count() > i) == false)
						error = QString("Vertex position attribute out of range for face %1").arg(fi);
				}

				for (int i : f.normalIndex)
				{
					if ((mFaceData.mVertexNormals.count() > i) == false)
						error = QString("Vertex normal attribute out of range for face %1").arg(fi);
				}

				for (int i : f.textureIndex)
				{
					if ((mFaceData.mTextureCoordinates.count() > i) == false)
						error = QString("Texture coordinate attribute out of range for face %1").arg(fi);
				}

				if (!error.isEmpty())
					break;
			}
		}

		if (!error.isEmpty())
		{
			QString formattedError = mFilepath + QString(" - Error: ") + error;
			qFatal(formattedError.toStdString().c_str());
		}
	}


	void Mesh::uploadIndexData()
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
					indexBuffer.append(PrimitiveRestartIndex);

				for (int v : f.vertexIndex)
				{
					Q_UNUSED(v);
					indexBuffer.append(i++);
				}
			}

			mRenderInfo.indexCount = indexBuffer.count();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.count()*sizeof(GLuint), &indexBuffer[0], GL_STATIC_DRAW);
		}
	}


	void Mesh::uploadVertexData()
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

			glUniform1i(mUniforms.indexCount, vertexIndicies.count());
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

			glBufferData(GL_ARRAY_BUFFER, vertexIndicies.count()*sizeof(GLuint), &vertexIndicies[0], GL_STATIC_DRAW);
			
			glVertexAttribIPointer(0, 1, GL_INT, 0, NULL);
			glEnableVertexAttribArray(0);

			glVertexAttribIPointer(1, 1, GL_INT, 0, (void*)normalOffset);
			glEnableVertexAttribArray(1);

			glVertexAttribIPointer(2, 1, GL_INT, 0, (void*)textureOffset);
			glEnableVertexAttribArray(2);
		}
	}
}
