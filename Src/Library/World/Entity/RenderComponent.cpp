//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "RenderComponent.h"
#include <Core/Mesh/OBJ.h>

namespace t3d { namespace World { namespace Entity
{
	RenderComponent::RenderComponent(BaseEntity *baseEntity) :
		Component(baseEntity)
	{
	}


	void RenderComponent::loadMesh(const QString &filepath)
	{
		mMesh = strong<OBJ>(new OBJ);
		mMesh->initWithFile(filepath);
	}


	void RenderComponent::render(const Mat4 &cameraMatrix)
	{
		Mat4 transformation = glm::translate(baseEntity()->pos());

		mMesh->render(cameraMatrix * transformation);
	}
}}}