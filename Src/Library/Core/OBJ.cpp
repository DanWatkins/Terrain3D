//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OBJ.h"

namespace t3d
{
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


	void OBJ::render()
	{
		mProgram.bind();
		{
			glBindVertexArray(mVao);
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLE_STRIP, mFaces.size()*5, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);
		}
		mProgram.release();
	}


	///// PRIVATE

	bool OBJ::parseField(const QStringList &field)
	{
		bool error = false;

		//4 component fields
		if (field.size() == 4)
		{
			//vertex
			if (field.front() == "v")
			{
				Vertex vertex;
				vertex.values[0] = field.at(1).toFloat();
				vertex.values[1] = field.at(2).toFloat();
				vertex.values[2] = field.at(3).toFloat();
				mVertecies.push_back(vertex);
			}
			else
				error = true;
		}
		//5 component fields
		else if (field.size() == 5)
		{
			//face
			if (field.front() == "f")
			{
				Face face;
				face.indicies[0] = field.at(1).toInt();
				face.indicies[1] = field.at(2).toInt();
				face.indicies[2] = field.at(3).toInt();
				face.indicies[3] = field.at(4).toInt();
				face.indicies[4] = PrimitiveRestartIndex;
				mFaces.push_back(face);
			}
			else
				error = true;
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
			error = true;

		return !error;
	}


	void OBJ::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, gDefaultPathShaders + "mesh-obj-vert.glsl");
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, gDefaultPathShaders + "mesh-obj-frag.glsl");

		if (mProgram.link() == false)
			printf("Problem linking OBJ mesh shadres\n");
		else
			printf("Initialized OBJ mesh shaders\n");
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
				int size = sizeof(GLuint)*5*mFaces.size();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &mFaces[0], GL_STATIC_DRAW);
			}
		}
		glBindVertexArray(0);
	}
}
