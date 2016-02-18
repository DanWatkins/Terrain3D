
//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "BaseEntity.h"
#include "RenderComponent.h"

namespace t3d { namespace world { namespace entity {

BaseEntity::BaseEntity(int id) :
	mId(id)
{
}


BaseEntity::~BaseEntity() {}


RenderComponent* BaseEntity::renderComponent() const
{
	return mRenderComponent.get();
}

void BaseEntity::createRenderComponent()
{
	if (!mRenderComponent)
		mRenderComponent = unique<RenderComponent>(new RenderComponent(this));
}

}}}
