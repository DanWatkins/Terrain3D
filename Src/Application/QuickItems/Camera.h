//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_QUICK_ITEMS_CAMERA_H
#define _t3d_QUICK_ITEMS_CAMERA_H

#include <memory>

#include <Core/OpenGLQuickItem.h>
#include <World/Camera.h>

namespace t3d { namespace QuickItems
{
	class Camera : public OpenGLQuickItem
	{
	public:
		Camera() :
			OpenGLQuickItem(&mRenderable)
		{
		}

	private:
		class Renderable : public IOpenGLRenderable, protected OpenGLFunctions
		{
		public:
			void init() override
			{
				initializeOpenGLFunctions();
				glClearColor(0.3f, 0.6f, 0.2f, 1.0f);
			}


			void render() override
			{
				glClear(GL_COLOR_BUFFER_BIT);
			}
		} mRenderable;
	};
}}

#endif


