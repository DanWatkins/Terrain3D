//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"

#include <World/Entity/BaseEntity.h>
#include <World/Entity/RenderComponent.h>

using namespace t3d::world::entity;
#define CLASS Test_WorldEntityBaseEntity

TEST_CLASS
{
protected:
};


TEST_CASE(defaultState)
{
	BaseEntity entity(1);
	ASSERT_NULL(entity.renderComponent());
	ASSERT_EQ(0.0, entity.pos().x);
	ASSERT_EQ(0.0, entity.pos().y);
	ASSERT_EQ(0.0, entity.pos().z);
}


TEST_CASE(createRenderableAndRender)
{
	BaseEntity entity(1);
	entity.createRenderComponent();

	RenderComponent *cmp = entity.renderComponent();
	ASSERT_NOT_NULL(cmp);

	//ensure the internal component doesn't get recreated on subsequent creates
	entity.createRenderComponent();
	ASSERT_EQ(cmp, entity.renderComponent());

	//can't really test the render
	entity.renderComponent()->render(Mat4(1.0f));
}