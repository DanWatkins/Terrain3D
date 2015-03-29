//==================================================================================================================|
// Created 2015.03.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_ResourceLoader_H
#define _t3d_core_ResourceLoader_H

#include <Library.h>
#include "OpenGLFunctions.h"

namespace t3d { namespace core
{
	class ResourceLoader : protected OpenGLFunctions
	{
	public:
		using TaskFunction = std::function<void(OpenGLFunctions*)>;

		void init();
		void addTask(TaskFunction f);
		void runTasks();

	private:
		QList<TaskFunction> mTasks;
	};
}}

#endif

