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

namespace t3d
{
	class Mesh : protected OpenGLFunctions
	{
	public:
		Mesh();
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
		QOpenGLShaderProgram mProgram;

		static const GLuint PrimitiveRestartIndex = 900000000;

		class MaterialData;
		QList<strong<MaterialData>> mMaterials;
		
		class FaceData;
		strong<FaceData> mFaceData;

		class SubMesh;
		QList<strong<SubMesh>> mSubMesh;

		struct Face
		{
			QVector<int> vertexIndex;
			QVector<int> textureIndex;
			QVector<int> normalIndex;
		};

		struct Uniforms
		{
			GLuint matrixCamera;
			GLuint matrixModel;
			GLint indexCount;
		} mUniforms;
	};
}

#endif

