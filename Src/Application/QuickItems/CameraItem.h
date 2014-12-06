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
	class CameraItem : public OpenGLQuickItem
	{
	private:
		typedef t3d::World::Camera ActualCamera;

	public:
		CameraItem() :
			OpenGLQuickItem(&mRenderable)
		{
		}

		void setWorld(t3d::World::World *world)	//TODO pass a const World*
		{
			mRenderable.mCamera = QSharedPointer<ActualCamera>(new ActualCamera(world));
		}

		QWeakPointer<ActualCamera> camera() { return mRenderable.mCamera; }

	private:
		class Renderable : public IOpenGLRenderable, protected OpenGLFunctions
		{
		public:
			void init() override
			{
				initializeOpenGLFunctions();
				mCamera->init();
			}


			void render() override
			{
				glClear(GL_COLOR_BUFFER_BIT);

				if (mCamera != nullptr)
				{
					glEnable(GL_DEPTH_TEST);
					glDepthMask(GL_TRUE);
					glDepthFunc(GL_LEQUAL);

					glClearColor(1.0f, 0.9f, 0.8f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

					//const qreal retinaScale = devicePixelRatio(); TODO
					//glViewport(0, 0, width() * retinaScale, height() * retinaScale);
					glViewport(0, 0, 800, 600);

					mCamera->render();
				}
			}

			QSharedPointer<ActualCamera> mCamera;
		} mRenderable;
	};
}}

#endif


