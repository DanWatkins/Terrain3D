//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Core_Asset_Mesh_H
#define _t3d_Core_Asset_Mesh_H

#include <Library.h>
#include <Core/OpenGLFunctions.h>

namespace t3d { namespace Asset
{
	class OBJ;

	class Mesh
	{
	public:
		friend class OBJ;

		Mesh();
		bool initWithFile(const QString &filepath);
		void render(const Mat4 &totalMatrix);
		QString name() const;


	private:
		class MeshPrivate;
		strong<MeshPrivate> mPrivate;
	};
}}

#endif

