//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "BaseEntity.h"

namespace t3d { namespace World { namespace Entity
{
	void BaseEntity::RenderComponent::loadMesh(const QString &filepath)
	{
		mMesh.initWithFile(filepath);
	}


	void BaseEntity::RenderComponent::render(const Mat4 &cameraMatrix)
	{
		mMesh.render(cameraMatrix);
	}
}}}