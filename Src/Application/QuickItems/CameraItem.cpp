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
		if (!mCamera)
		{
			mCamera = unique<World::Camera>(new World::Camera);

			QObject::connect(window(), SIGNAL(beforeRendering()), mCamera.get(), 
							 SLOT(render()), Qt::DirectConnection);

			QObject::connect(mCamera.get(), SIGNAL(finishedRendering()),
							 this, SLOT(cameraFinishedRendering()), Qt::DirectConnection);
		}
	}


	void CameraItem::cleanup()
	{
	}


	void CameraItem::cameraFinishedRendering()
	{
		window()->resetOpenGLState();
	}



	/*void render()
	{
		if (theCamera)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LEQUAL);

			QSize frameSize = framebufferObject()->size();
			theCamera->resize(frameSize.width(), frameSize.height());	//TODO pass QSize instead

			glClearColor(1.0f, 0.9f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//const qreal retinaScale = devicePixelRatio(); TODO
			//glViewport(0, 0, width() * retinaScale, height() * retinaScale);
			glViewport(0, 0, frameSize.width(), frameSize.height());

			theCamera->render();
		}
		else
		{
			glClearColor(1.0f, 0.3f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		update();
	}*/
}}
