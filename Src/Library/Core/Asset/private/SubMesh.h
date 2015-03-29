//==================================================================================================================|
// Created 2015.01.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_SUB_MESH_H
#define _t3d_CORE_SUB_MESH_H

#include "MeshPrivate.h"
#include "FaceData.h"

namespace t3d { namespace asset
{
	class mesh_p::SubMesh : public core::OpenGLFunctions
	{
	public:
		GLuint mVao;
		QVector<Face> mFaces;
		int mIndexCount = 0;	//number of indicies in the index buffer including restart indicies
		QString mMaterial;

		void uploadData();
		void render();
		void bind();
		void unbind();

		void checkForErrors(const FaceData *faceData, QString &error);

	private:
		void uploadIndexData();
		void uploadVertexData();
	};
}}

#endif

