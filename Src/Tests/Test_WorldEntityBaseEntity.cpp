//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"

#include <World/Entity/BaseEntity.h>

using namespace t3d::World::Entity;
#define CLASS Test_WorldEntityBaseEntity

TEST_CLASS
{
protected:
};


TEST_CASE(defaultState)
{
	BaseEntity entity(1);
	ASSERT_NULL(entity.cmp_renderable());
	ASSERT_EQ(0.0, entity.pos().x);
	ASSERT_EQ(0.0, entity.pos().y);
	ASSERT_EQ(0.0, entity.pos().z);
}


TEST_CASE(createRenderableAndRender)
{
	BaseEntity entity(1);
	entity.createCmp_renderable();

	BaseEntity::RenderComponent *cmp = entity.cmp_renderable();
	ASSERT_NOT_NULL(cmp);

	//ensure the internal component doesn't get recreated on subsequent creates
	entity.createCmp_renderable();
	ASSERT_EQ(cmp, entity.cmp_renderable());

	//can't really test the render
	entity.cmp_renderable()->render(Mat4(1.0f));
}