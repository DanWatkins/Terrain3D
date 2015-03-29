//==================================================================================================================|
// Created 2015.03.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLTaskQueue.h"

namespace t3d { namespace core
{
	void OpenGLTaskQueue::init()
	{
		QMutexLocker m(&mMutex);
		initializeOpenGLFunctions();
	}


	void OpenGLTaskQueue::addTask(TaskFunction f)
	{
		QMutexLocker m(&mMutex);
		mTasks.append(f);
	}


	void OpenGLTaskQueue::runTasks()
	{
		QMutexLocker m(&mMutex);

		for (TaskFunction &tf : mTasks)
		{
			tf((BaseOpenGLFunctions*)this);
		}

		mTasks.clear();
	}
}}