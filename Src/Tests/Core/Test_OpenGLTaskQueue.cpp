//==================================================================================================================|
// Created 2015.03.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "../Tests.h"
#include <Core/OpenGLTaskQueue.h>
#include <Core/MutexTryLocker.h>

using namespace t3d::core;

#define CLASS Test_ResourceLoader

TEST_CLASS
{
protected:

};


TEST_CASE(AddTaskAsync)
{
	OpenGLTaskQueue taskQueue;
	taskQueue.init();

	//TODO make a relative ordering test helper
	bool t1Happened = false;
	bool t2Happened = false;
	QMutex mutex;

	//add tasks in a different thread
	std::thread f([&]
	{
		//task 1
		taskQueue.addTask([&](BaseOpenGLFunctions *gl)
		{
			ASSERT_TRUE(QGuiApplication::instance()->thread() == QThread::currentThread()) << "Task not on main thread";
			ASSERT_NOT_NULL(gl);

			MutexTryLocker l(&mutex);
			ASSERT_TRUE(l.isLocked());	//TODO this is a weak attemt at verifying thread safety

			//as long as calling these functions doesn't crash...we are good
			gl->glGetString(GL_VERSION);
			gl->glGetString(GL_VENDOR);
			gl->glGetString(GL_RENDERER);

			ASSERT_FALSE(t2Happened);
			t1Happened = true;
		});

		//task 2
		taskQueue.addTask([&](BaseOpenGLFunctions *gl)
		{
			ASSERT_TRUE(QGuiApplication::instance()->thread() == QThread::currentThread()) << "Task not on main thread";
			ASSERT_NOT_NULL(gl);

			MutexTryLocker l(&mutex);
			ASSERT_TRUE(l.isLocked());	//TODO this is a weak attemt at verifying thread safety

			gl->glBindTexture(GL_TEXTURE_2D, 0);
			
			ASSERT_TRUE(t1Happened);
			t2Happened = true;
		});
	});

	f.join();
	taskQueue.runTasks();

	ASSERT_TRUE(t1Happened);
	ASSERT_TRUE(t2Happened);
}


TEST_CASE(ClearOutTasksAfterRunning)
{
	OpenGLTaskQueue taskQueue;
	taskQueue.init();
	int execCount = 0;

	auto task = [&execCount](BaseOpenGLFunctions *gl) { ++execCount; };

	taskQueue.addTask(task);
	taskQueue.addTask(task);

	taskQueue.runTasks();
	ASSERT_EQ(2, execCount);

	execCount = 0;

	//there should not be any tasks queued to run
	taskQueue.runTasks();
	ASSERT_EQ(0, execCount);
}
