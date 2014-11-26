//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OBJ.h"

namespace t3d
{
	OBJ::OBJ()
	{
	}


	bool OBJ::load(const QString &filepath)
	{
		OpenGLFunctions::initializeOpenGLFunctions();
		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream ts(&file);
		int lineNumber = 0;

		while (!ts.atEnd())
		{
			QString line = ts.readLine();
			QStringList field = line.split(" ");

			if (!parseField(field))
			{
				qDebug() << filepath << "- Error parsing line " << lineNumber << ": " << line;
			}

			++lineNumber;
		}

		loadShaders();
		uploadData();

		return true;
	}


	void OBJ::render(const Mat4 &totalMatrix)
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
							   glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			glBindVertexArray(mVao);
			{
				glLineWidth(1.0f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				//TODO glDrawElements(GL_TRIANGLE_STRIP, mIndicies.size(), GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);
		}
		mProgram.release();
	}


	///// PRIVATE

	bool OBJ::parseField(const QStringList &field)
	{
		//vertex
		if (field.front() == "v"  &&  field.size() == 4)
		{
			Vertex vertex;
			vertex.values[0] = field.at(1).toFloat();
			vertex.values[1] = field.at(2).toFloat();
			vertex.values[2] = field.at(3).toFloat();
			mVertecies.push_back(vertex);
		}
		//vertex normal
		else if (field.front() == "vn"  &&  field.size() == 4)
		{
			Vertex vertex;
			vertex.values[0] = field.at(1).toFloat();
			vertex.values[1] = field.at(2).toFloat();
			vertex.values[2] = field.at(3).toFloat();
			mVertexNormals.push_back(vertex);
		}
		//face
		else if (field.front() == "f"  &&  field.size() >= 4)
		{
			Face face;

			for (int i=0; i<field.size()-1; i++)
			{
				QStringList cmp = field.at(i+1).split("/");

				if (cmp.size() > 0)
					face.vertexIndex.push_back(cmp.at(0).toInt()-1);
				if (cmp.size() > 1)
					face.textureIndex.push_back(cmp.at(1).toInt()-1);
				if (cmp.size() > 2)
					face.normalIndex.push_back(cmp.at(2).toInt()-1);

				//mIndicies.push_back(field.at(i+1).toInt()-1);
			}

			mFaces.push_back(face);

			//mIndicies.push_back(PrimitiveRestartIndex);
		}
		//comment
		else if (field.at(0).startsWith("#"))
		{
			//do nothing
		}
		//blank line
		else if (field.size() == 0)
		{
			//do nothing
		}
		else
			return false;

		return true;
	}


	void OBJ::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, gDefaultPathShaders + "mesh-obj-vert.glsl");
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, gDefaultPathShaders + "mesh-obj-frag.glsl");

		if (mProgram.link() == false)
			printf("Problem linking OBJ mesh shadres\n");
		else
			printf("Initialized OBJ mesh shaders\n");

		mProgram.bind();
		{
			mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
			mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
		}
		mProgram.release();
	}


	void OBJ::uploadData()
	{
		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(PrimitiveRestartIndex);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			{
				int size = sizeof(GLfloat)*3*mVertecies.size();
				glBufferData(GL_ARRAY_BUFFER, size, &mVertecies[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);
			}

			GLuint ibo;
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			{
				//TODO glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mIndicies.size(), &mIndicies[0], GL_STATIC_DRAW);
			}
		}
		glBindVertexArray(0);
	}
}
