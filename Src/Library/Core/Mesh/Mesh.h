//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_MESH_H
#define _t3d_CORE_MES_H

#include <Library.h>
#include <Core/OpenGLFunctions.h>

namespace t3d
{
	class Mesh : protected OpenGLFunctions
	{
	public:
		void render(const Mat4 &totalMatrix);

	protected:
		void init();

		void loadShaders();
		void uploadData();
		void checkForErrors();

		void uploadIndexData();
		void uploadVertexData();
		void uploadMaterialData();

		void uploadVertexPositions();
		void uploadVertexNormals();
		void uploadTextureCoordinates();

	protected:
		QString mContainingDirectory;
		QString mFilepath;
		QString mName;

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
		QVector<Vertex> mTextureCoordinates;
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


		struct Textures
		{
			GLuint material;
			GLuint bufferVertexPositions;
			GLuint bufferVertexNormals;
			GLuint bufferTextureCoordinates;

		} mTextures;
	};
}

#endif

