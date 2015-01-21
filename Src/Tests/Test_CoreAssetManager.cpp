//==================================================================================================================|
// Created 2015.01.21 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"

#include <Core/AssetManager.h>

using namespace t3d;
#define CLASS Test_CoreAssetManager
#define TEST_DIR gTestDir + "Test_CoreAssetManager/"

TEST_CLASS
{
protected:
};



TEST_CASE(loadMeshesFromDirectory)
{
	/* IDK MAN, Qt context issue here without a window
	QQuickWindow window;

	AssetManager am;
	am.loadMeshesFromDirectory(TEST_DIR + "loadMeshesFromDirectory/");

	ASSERT_EQ(am.meshCount(), 1);
	ASSERT_NOT_NULL(am.meshForName("Cube"));

	//ensure some that shouldn't exist, doesn't exist
	ASSERT_NULL(am.meshForName("NotExist"));
	*/
}