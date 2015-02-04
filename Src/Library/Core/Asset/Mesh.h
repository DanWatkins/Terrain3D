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
	class Manager;

	class Mesh
	{
	public:
		friend class Manager;
		Mesh();

		bool init(Manager *manager, const QString &filepath);
		void queueRender(const Mat4 &totalMatrix);
		QString name() const;

		class MeshPrivate;

	private:
		strong<MeshPrivate> mPrivate;
		Manager *mManager = nullptr;
		void batchRender(const QVector<Mat4> &matricies);
	};
}}

#endif

