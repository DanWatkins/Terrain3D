//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "CameraItem.h"

namespace t3d { namespace QuickItems
{
	CameraItem::CameraItem() :
		mIsFrozen(false)
	{
		QObject::connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
	}


	void CameraItem::handleWindowChanged(QQuickWindow *window)
	{
		if (window)
		{
			QObject::connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
			QObject::connect(window, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
			window->setClearBeforeRendering(false);
		}
	}


	void CameraItem::sync()
	{
		if (!mIsSynced && mCamera)
		{
			QObject::connect(window(), SIGNAL(beforeRendering()),
								 this, SLOT(render()), Qt::DirectConnection);

			QObject::connect(mCamera.get(), SIGNAL(finishedRendering()),
								this, SLOT(cameraFinishedRendering()), Qt::DirectConnection);

			mIsSynced = true;
		}
		else if (!mCamera)
		{
			System::fatal("CameraItem hasn't had it's internal world::Camera created yet");
		}
	}


	weak<world::Camera> CameraItem::createCamera()
	{
		if (!mCamera)
		{
			mCamera = strong<world::Camera>(new world::Camera);
		}

		return mCamera;
	}


	void CameraItem::cleanup()
	{
		mCamera->cleanup();
	}


	void CameraItem::cameraFinishedRendering()
	{
		window()->resetOpenGLState();
	}


	void CameraItem::render()
	{
        if (mCamera && mCamera->pHasLoaded)
		{
			mCamera->resize(width(), height());
			mCamera->render();
		}
		else
		{
			glClearColor(1.0f, 0.3f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		window()->update();
	}
}}
