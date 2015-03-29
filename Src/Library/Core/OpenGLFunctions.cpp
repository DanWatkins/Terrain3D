//==================================================================================================================|
// Created 2015.03.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLFunctions.h"

namespace t3d { namespace core
{
	OpenGLFunctions::OpenGLFunctions(OpenGLTaskQueue *taskQueue) :
		mTaskQueue(taskQueue)
	{
		if (!taskQueue)
			qFatal("Null OpenGLTaskQueue");
	}


	OpenGLFunctions::OpenGLFunctions(OpenGLFunctions *other) :
		OpenGLFunctions(other->taskQueue())
	{
	}
}}