//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_OBJ_H
#define _t3d_CORE_OBJ_H

#include <Library.h>
#include <Core/Image.h>
#include <Core/OpenGLFunctions.h>

namespace t3d
{
	class OBJ : protected OpenGLFunctions
	{
	public:
		OBJ();

		bool initWithFile(const QString &filepath);
		void render(const Mat4 &totalMatrix);

	private:
		QString mContainingDirectory;

		struct Vertex
		{
			GLfloat values[3];
		};

		struct Face
		{
			QVector<int> vertexIndex;
			QVector<int> textureIndex;
			QVector<int> normalIndex;
		};

		QVector<Vertex> mVertecies;
		QVector<Vertex> mVertexNormals;
		QVector<Face> mFaces;

		QOpenGLShaderProgram mProgram;
		GLuint mVao;

		struct RenderInfo
		{
			int indexCount = 0;	//number of indicies in the index buffer including restart indicies
		} mRenderInfo;

		const GLuint PrimitiveRestartIndex = 900000000;

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLint indexCount;
		} mUniforms;


		struct Material
		{
			QString name;
			QString filepath;
		} mMaterial;

	private:
		bool parseFile(const QString &filepath);
		bool parseField(const QStringList &field);
		bool parseMaterialLib(const QString &filepath);
		bool parseMaterialLibField(const QStringList &field);
		void init();

		void loadShaders();
		void uploadData();

		void uploadIndexData();
		void uploadVertexData();
		void uploadMaterialData();

		void uploadVertexPositions();
		void uploadVertexNormals();
	};
}

#endif

