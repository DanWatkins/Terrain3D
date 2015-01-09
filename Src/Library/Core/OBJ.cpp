//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OBJ.h"

namespace t3d
{
	OBJ::OBJ()
	{
	}


	void removeLastPathComponent(QString &filepath)
	{
		filepath = "../Meshes/"; //TODO massive temporary hack
	}


	bool OBJ::initWithFile(const QString &filepath)
	{
		OpenGLFunctions::initializeOpenGLFunctions();
		
		mContainingDirectory = filepath;
		removeLastPathComponent(mContainingDirectory);
		
		bool result;
		if (result = parseFile(filepath))
			init();

		return result;
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
				glDrawElements(GL_TRIANGLE_FAN, mRenderInfo.indexCount, GL_UNSIGNED_INT, 0); // TODO MAJOR
				//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glBindVertexArray(0);
		}
		mProgram.release();
	}


	///// PRIVATE

	bool OBJ::parseFile(const QString &filepath)
	{
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

		return true;
	}


	bool OBJ::parseField(const QStringList &field)
	{
		//material lib
		if (field.front() == "mtllib" && field.count() == 2)
		{
			parseMaterialLib(mContainingDirectory + "/" + field.at(1));
		}

		//vertex
		else if (field.front() == "v"  &&  field.size() == 4)
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
			}

			mFaces.push_back(face);
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


	bool OBJ::parseMaterialLib(const QString &filepath)
	{
		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream ts(&file);
		int lineNumber = 0;

		while (!ts.atEnd())
		{
			QString line = ts.readLine();
			QStringList field = line.split(" ");

			if (!parseMaterialLibField(field))
			{
				qDebug() << filepath << "- Error parsing line " << lineNumber << ": " << line;
			}

			++lineNumber;
		}

		return true;
	}


	bool OBJ::parseMaterialLibField(const QStringList &field)
	{
		//new material
		if (field.front() == "newmtl" && field.count() == 2)
		{
			mMaterial.name = field.at(1);
		}
		//texture map - diffuse
		else if (field.front() == "map_Kd" && field.count() == 2)
		{
			mMaterial.filepath = field.at(1);
		}
		else
		{
			//unknown
			return false;
		}

		return true;
	}


	void OBJ::init()
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

	
	void OBJ::loadShaders()
	{
		QOpenGLShader vertexShader(QOpenGLShader::Vertex, nullptr);
		vertexShader.compileSourceFile(gDefaultPathShaders + "mesh-obj-vert.glsl");
		mProgram.addShader(&vertexShader);

		QOpenGLShader fragmentShader(QOpenGLShader::Fragment, nullptr);
		fragmentShader.compileSourceFile(gDefaultPathShaders + "mesh-obj-frag.glsl");
		mProgram.addShader(&fragmentShader);

		if (mProgram.link() == false)
			printf("Problem linking OBJ mesh shadres\n");
		else
			printf("Initialized OBJ mesh shaders\n");
	}


	void OBJ::uploadData()
	{
		uploadVertexPositions();
		uploadVertexNormals();

		uploadIndexData();
		uploadVertexData();
		uploadMaterialData();
	}


	void OBJ::uploadIndexData()
	{
		GLuint ibo;
		glGenBuffers(1, &ibo);
		qDebug() << "ibo=" << ibo;
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


	void OBJ::uploadVertexData()
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		qDebug() << "vbo=" << vbo;
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

			glBufferData(GL_ARRAY_BUFFER, vertexIndicies.count()*sizeof(GLuint), &vertexIndicies[0], GL_STATIC_DRAW);
			
			glVertexAttribIPointer(0, 1, GL_INT, 0, NULL);
			glEnableVertexAttribArray(0);

			glVertexAttribIPointer(1, 1, GL_INT, 0, (void*)normalOffset);
			glEnableVertexAttribArray(1);
		}
	}


	void OBJ::uploadMaterialData()
	{
		Image image;
		image.loadFromFile_PNG(mContainingDirectory + mMaterial.filepath);

		//todo finish
	}


	void OBJ::uploadVertexPositions()
	{
		GLuint texture;
		glGenTextures(1, &texture);

		qDebug() << "textureVertexPositions: " << texture;
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_BUFFER, texture);
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			qDebug() << "vertPos: " << buffer;
			glBindBuffer(GL_TEXTURE_BUFFER, buffer);
			{
				glBufferData(GL_TEXTURE_BUFFER, mVertecies.count()*3*sizeof(GLfloat), &mVertecies[0], GL_STATIC_DRAW);
				glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer);
			}
		}
	}


	void OBJ::uploadVertexNormals()
	{
		GLuint texture;
		glGenTextures(1, &texture);

		qDebug() << "textureVertexNormals: " << texture;
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_BUFFER, texture);
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			qDebug() << "vertNormals: " << buffer;
			glBindBuffer(GL_TEXTURE_BUFFER, buffer);
			{
				glBufferData(GL_TEXTURE_BUFFER, mVertexNormals.count()*3*sizeof(GLfloat), &mVertexNormals[0], GL_STATIC_DRAW);
				glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer);
			}
		}
	}		
}
