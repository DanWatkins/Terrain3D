//==================================================================================================================|
// Created 2015.03.28by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ResourceLoader.h"

namespace t3d { namespace core
{
	void ResourceLoader::init()
	{
		initializeOpenGLFunctions();
	}


	void ResourceLoader::addTask(std::function<void(OpenGLFunctions*)> f)
	{
		mTasks.append(f);
	}


	void ResourceLoader::runTasks()
	{
		for (TaskFunction &tf : mTasks)
			tf(this);
	}
}}