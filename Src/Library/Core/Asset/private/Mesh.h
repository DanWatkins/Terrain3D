//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_MESH_H
#define _t3d_CORE_MESH_H

#include <Library.h>
#include <Core/OpenGLFunctions.h>

namespace t3d { namespace Asset
{
	class Mesh : protected OpenGLFunctions
	{
	public:
		Mesh();
		void init();
		void render(const Mat4 &totalMatrix);

		void setFilepath(const QString &filepath);
		QString filepath() { return mFilepath; }
		QString containingDirectory() { return mContainingDirectory; }
		void setName(const QString &name);
		QString name() { return mName; }

	protected:
		struct Vertex
		{
			GLfloat values[3];
		};

		static const GLuint PrimitiveRestartIndex = 900000000;

		class MaterialData;
		class FaceData;
		class SubMesh;

		struct Face
		{
			QVector<int> vertexIndex;
			QVector<int> textureIndex;
			QVector<int> normalIndex;
		};

		QList<strong<MaterialData>> mMaterials;

	private:
		QString mContainingDirectory;
		QString mFilepath;
		QString mName;
		QOpenGLShaderProgram mProgram;

		strong<FaceData> mFaceData;
		QList<strong<SubMesh>> mSubMesh;

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLint indexCount;
		} mUniforms;

		void loadShaders();
		void uploadData();
		void checkForErrors();


	protected:
		void makeSubMesh();
		strong<SubMesh> currentSubMesh();
		void addVertexPosition(const Vertex &vertex);
		void addVertexNormal(const Vertex &normal);
		void addTextureCoordinate(const Vertex &texCoord);
	};
}}

#endif

