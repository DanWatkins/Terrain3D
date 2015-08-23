//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Entity_Component_H
#define _t3d_World_Entity_Component_H

#include "BaseEntity.h"

namespace t3d { namespace world { namespace entity
{
	class Component
	{
	public:
		Component() = delete;
		Component(BaseEntity *baseEntity) { mBaseEntity = baseEntity; }
		virtual ~Component() {}

	protected:
		BaseEntity* baseEntity() { return mBaseEntity; }

	private:
		BaseEntity *mBaseEntity;
	};
}}}

#endif

