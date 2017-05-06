//==================================================================================================================|
// Created 2015.03.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_core_OpenGLTaskQueue_H
#define _t3d_core_OpenGLTaskQueue_H

#include <Terrain3D/Library.h>
#include <Terrain3D/Core/OpenGLFunctions.h>

namespace t3d { namespace core {

/**
 * \brief Utility for queueing up tasks to be executed on the main thread with access to OpenGLFunctions.
 * This is entirely thread-safe, so tasks can be queued from multiple threads.
 */
class OpenGLTaskQueue : protected OpenGLFunctions
{
public:
    using TaskFunction = std::function<void(OpenGLFunctions*)>;

    /**
     * Gets the internal OpenGLFunctions ready to go.
     */
    void init();

    /**
     * Adds a task function to the queue which will be exectued when runTasks is called.
     */
    void addTask(TaskFunction f);

    /**
     * Call this on the main thread to process all tasks. The task queue will be empty afterwards.
     */
    void runTasks();

private:
    QMutex mMutex;
    QList<TaskFunction> mTasks;
};

}}

#endif

