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
	  mDevice(0),
	  mCapturesCursor(false),
	  mMouseButtonLeftPressed(false)
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


void OpenGLWindow::mousePressEvent(QMouseEvent *ev)
{
	std::cout << "Mouse press" << std::endl;

	if (QWindow::isActive())
	{
		if (ev->button() == Qt::LeftButton)
		{
			//force the last cursor position to update (zero it out)
			consumeCursorDelta();
			mMouseButtonLeftPressed = true;
		}
	}
}


void OpenGLWindow::mouseReleaseEvent(QMouseEvent *ev)
{
	std::cout << "Mouse release" << std::endl;

	if (QWindow::isActive())
	{
		if (ev->button() == Qt::LeftButton)
		{
			mMouseButtonLeftPressed = false;
		}
	}
}

const float mouseDeltaOffsetX = 100.0f;
const float mouseDeltaOffsetY = 100.0f;

QVector2D OpenGLWindow::consumeCursorDelta()
{
	QVector2D delta;

#ifdef WIN32
	POINT pos;
	GetCursorPos(&pos);
	delta = QVector2D(float(pos.x - mLastCursorPos.x), float(pos.y - mLastCursorPos.y));
#else
	#error No mouse delta function for this platform.
#endif

	mLastCursorPos = Vec2i(pos.x, pos.y);

	return delta;
}


void OpenGLWindow::resetCursorPosition()
{
	if (mCapturesCursor == false)
		return;

#ifdef WIN32
	SetCursorPos(mouseDeltaOffsetX, mouseDeltaOffsetY);
#else
	#error No mouse delta function for this platform
#endif

	mLastCursorPos = Vec2i(mouseDeltaOffsetX, mouseDeltaOffsetY);
}
