//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "CameraItem.h"

namespace t3d { namespace QuickItems
{
	CameraItem::CameraItem() :
		mIsLoaded(false)
	{
	}


	void CameraItem::setWorld(t3d::World::World *world)	//TODO pass a const World*
	{
		mCamera = QSharedPointer<ActualCamera>(new ActualCamera(world));
	}


	void CameraItem::init()
	{
		initializeOpenGLFunctions();
		mCamera->init();
		mCamera->resize(width(), height());
		setIsLoaded(true);
	}


	void CameraItem::render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if (mCamera != nullptr)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LEQUAL);

			mCamera->resize(width(), height());	//TODO pass QSize instead

			glClearColor(1.0f, 0.9f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//const qreal retinaScale = devicePixelRatio(); TODO
			//glViewport(0, 0, width() * retinaScale, height() * retinaScale);
			glViewport(0, 0, width(), height());

			mCamera->render();
		}
	}


	void CameraItem::setIsLoaded(bool isLoaded)
	{
		if (isLoaded != mIsLoaded)
		{
			mIsLoaded = isLoaded;
			emit isLoadedChanged();
		}
	}
}}
