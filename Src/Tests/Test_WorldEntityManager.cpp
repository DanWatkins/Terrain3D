//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"

#include <World/Entity/Manager.h>

using namespace t3d::World::Entity;
#define CLASS Test_WorldEntityBaseEntity

TEST_CLASS
{
protected:

};

TEST_CASE(simpleCreateEntity)
{
	Manager manager;
	strong<BaseEntity> entity = manager.createEntity();
	ASSERT_TRUE(entity != nullptr);
	ASSERT_TRUE(entity->id().isValid());
}


TEST_CASE(createEntitiesUnique)
{
	Manager manager;
	strong<BaseEntity> e1 = manager.createEntity();
	strong<BaseEntity> e2 = manager.createEntity();
	strong<BaseEntity> e3 = manager.createEntity();

	ASSERT_NE(e1, e2);
	ASSERT_NE(e1, e3);
	ASSERT_NE(e2, e3);
}


TEST_CASE(createFindEntities)
{
	Manager manager;
	strong<BaseEntity> e1 = manager.createEntity();
	strong<BaseEntity> e2 = manager.createEntity();
	strong<BaseEntity> e3 = manager.createEntity();

	ASSERT_EQ(e1, manager.findEntity(e1->id()));
	ASSERT_EQ(e2, manager.findEntity(e2->id()));
	ASSERT_EQ(e3, manager.findEntity(e3->id()));
}