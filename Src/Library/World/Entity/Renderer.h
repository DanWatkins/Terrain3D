//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_RENDERER_H
#define _t3d_RENDERER_H

#include <Library.h>

#include <World/Entity/Manager.h>

namespace t3d { namespace world { namespace entity
{
	class Renderer
	{
	public:
		void setManager(Manager *manager) { mManager = manager; }
		void renderAll(const Mat4 &cameraMatrix);

	private:
		Manager *mManager;
	};
}}}

#endif

