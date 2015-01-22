//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mesh.h"

#include "./private/MeshPrivate.h"

namespace t3d { namespace Asset
{
	Mesh::Mesh() :
		mPrivate(new MeshPrivate)
	{
	}

	bool Mesh::initWithFile(const QString &filepath)
	{
		return mPrivate->initWithFile(filepath);
	}


	void Mesh::render(const Mat4 &totalMatrix)
	{
		mPrivate->render(totalMatrix);
	}


	QString Mesh::name() const
	{
		return mPrivate->name();
	}
}}