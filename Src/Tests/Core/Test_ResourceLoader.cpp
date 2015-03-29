//==================================================================================================================|
// Created 2015.03.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"
#include <Core/ResourceLoader.h>

using namespace t3d::core;

#define CLASS Test_ResourceLoader

TEST_CLASS
{
protected:

};


TEST_CASE(AddTaskAsync)
{
	ResourceLoader loader;
	loader.init();

	//TODO make a relative ordering test helper
	bool t1Happened = false;
	bool t2Happened = false;
	QMutex mutex;

	//add tasks in a different thread
	std::thread f([&]
	{
		//task 1
		loader.addTask([&](OpenGLFunctions *gl)
		{
			ASSERT_TRUE(mutex.tryLock());	//TODO this is a weak attemt at verifying thread safety
			ASSERT_NOT_NULL(gl);

			//as long as calling these functions doesn't crash...we are good
			gl->glGetString(GL_VERSION);
			gl->glGetString(GL_VENDOR);
			gl->glGetString(GL_RENDERER);

			ASSERT_FALSE(t2Happened);
			t1Happened = true;
			mutex.unlock();
		});

		//task 2
		loader.addTask([&](OpenGLFunctions *gl)
		{
			ASSERT_TRUE(mutex.tryLock());	//TODO this is a weak attemt at verifying thread safety
			ASSERT_NOT_NULL(gl);

			gl->glBindTexture(GL_TEXTURE_2D, 0);
			
			ASSERT_TRUE(t1Happened);
			t2Happened = true;
			mutex.unlock();
		});
	});

	f.join();
	loader.runTasks();

	ASSERT_TRUE(t1Happened);
	ASSERT_TRUE(t2Happened);
}