//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(QWindow *parent)
	: QWindow(parent),
	  mUpdatePending(false),
	  mAnimating(false),
	  mContext(0),
	  mDevice(0)
{
	setSurfaceType(QWindow::OpenGLSurface);
}


void OpenGLWindow::render(QPainter *painter)
{
	Q_UNUSED(painter);
}


void OpenGLWindow::initialize()
{
}


void OpenGLWindow::render()
{
	if (!mDevice)
		mDevice = new QOpenGLPaintDevice;

	mDevice->setSize(size());

	QPainter painter(mDevice);
	render(&painter);
}


void OpenGLWindow::renderLater()
{
	if (!mUpdatePending)
	{
		mUpdatePending = true;
		QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
	}
}


bool OpenGLWindow::event(QEvent *event)
{
	switch (event->type())
	{
		case QEvent::UpdateRequest:
		{
			mUpdatePending = false;
			renderNow();
			return true;
		}
		default:
		{
			return QWindow::event(event);
		}
	}
}


void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
	Q_UNUSED(event);

	if (isExposed())
		renderNow();
}


void OpenGLWindow::renderNow()
{
	if (!isExposed())
		return;

	bool needsInitialize = false;

	if (!mContext) {
		mContext = new QOpenGLContext(this);
		mContext->setFormat(requestedFormat());
		mContext->create();

		needsInitialize = true;
	}

	mContext->makeCurrent(this);

	if (needsInitialize) {
		initializeOpenGLFunctions();
		initialize();
	}

	render();

	mContext->swapBuffers(this);

	if (mAnimating)
		renderLater();
}


void OpenGLWindow::setAnimating(bool animating)
{
	mAnimating = animating;

	if (animating)
		renderLater();
}


const float mouseDeltaOffsetX = 100.0f;
const float mouseDeltaOffsetY = 100.0f;

QVector2D OpenGLWindow::getCursorDelta()
{
	QVector2D delta;

#ifdef WIN32
	POINT pos;
	GetCursorPos(&pos);
	pos.x -= mouseDeltaOffsetX;
	pos.y -= mouseDeltaOffsetY;
	delta = QVector2D(float(pos.x), float(pos.y));
#else
	#error No mouse delta function for this platform.
#endif

	return delta;
}


void OpenGLWindow::resetCursorPosition()
{
#ifdef WIN32
	SetCursorPos(mouseDeltaOffsetX, mouseDeltaOffsetY);
#else
	#error No mouse delta function for this platform
#endif
}