//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_OBJ_H
#define _t3d_CORE_OBJ_H

#include <Library.h>

namespace t3d { namespace Asset
{
	class Mesh;

	class OBJ
	{
	public:
		bool initWithFile(const QString &filepath, Mesh *mesh);

	private:
		Mesh *mCurrentMesh;

		bool parseFile(const QString &filepath);
		bool parseField(const QStringList &field);
		bool parseMaterialLib(const QString &filepath);
		bool parseMaterialLibField(const QStringList &field);
	};
}}

#endif

