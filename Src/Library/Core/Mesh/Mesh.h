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

		struct Vertex
		{
			GLfloat values[3];
		};

	private:
		void loadShaders();
		void uploadData();
		void checkForErrors();

		void uploadIndexData();
		void uploadVertexData();

		void uploadBufferAttribute(GLenum textureUnit, const QVector<Vertex> &data, GLuint &textureName);

	protected:
		QString mContainingDirectory;
		QString mFilepath;
		QString mName;

		class MaterialData : public OpenGLFunctions
		{
		public: //TODO massive
			QString mName;
			QString mFilepath;

			GLuint mMaterial;

			void uploadMaterialData(const QString &containingDirectory);
			void bind();
		} mMaterialData;
		

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

		struct Textures
		{
			GLuint bufferVertexPositions;
			GLuint bufferVertexNormals;
			GLuint bufferTextureCoordinates;

		} mTextures;
	};
}

#endif

