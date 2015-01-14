//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "BaseEntity.h"

namespace t3d { namespace World { namespace Entity
{
	BaseEntity::RenderComponent* BaseEntity::cmp_renderable() const
	{
		return mCmp_renderable.get();
	}


	void BaseEntity::createCmp_renderable()
	{
		mCmp_renderable = unique<RenderComponent>(new RenderComponent);
	}
}}}