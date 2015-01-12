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

	protected:
		QString mContainingDirectory;
		QString mFilepath;
		QString mName;

		static const GLuint PrimitiveRestartIndex = 900000000;

		class MaterialData : public OpenGLFunctions
		{
		public: //TODO massive
			QString mName;
			QString mFilepath;

			GLuint mMaterial;

			void uploadMaterialData(const QString &containingDirectory);
			void bind();
		} mMaterialData;
		

		class FaceData : public OpenGLFunctions
		{
		public:  //TODO massive
			QVector<Vertex> mVertecies;
			QVector<Vertex> mVertexNormals;
			QVector<Vertex> mTextureCoordinates;

			GLuint bufferVertexPositions;
			GLuint bufferVertexNormals;
			GLuint bufferTextureCoordinates;

			void uploadData();
			void bind();

		private:
			void uploadBufferAttribute(GLenum textureUnit, const QVector<Vertex> &data, GLuint &textureName);
		} mFaceData;

		struct Face
		{
			QVector<int> vertexIndex;
			QVector<int> textureIndex;
			QVector<int> normalIndex;
		};

		class SubMesh : public OpenGLFunctions
		{
		public:
			GLuint mVao;
			QVector<Face> mFaces;
			int mIndexCount = 0;	//number of indicies in the index buffer including restart indicies

			void uploadData();
			void render();

		private:
			void uploadIndexData();
			void uploadVertexData();
		} mSubMesh;

		QOpenGLShaderProgram mProgram;
		

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLint indexCount;
		} mUniforms;
	};
}

#endif

