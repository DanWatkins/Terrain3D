//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLQuickView.h"

namespace t3d
{
	OpenGLQuickView::OpenGLQuickView() :
		mUpdatePending(false),
		mAnimating(false),
		mCapturesCursor(false),
		mMouseButtonLeftPressed(false)
	{

	}


	void OpenGLQuickView::mousePressEvent(QMouseEvent *ev)
	{
		QQuickView::mousePressEvent(ev);

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


	void OpenGLQuickView::mouseReleaseEvent(QMouseEvent *ev)
	{
		QQuickView::mouseReleaseEvent(ev);

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

	QVector2D OpenGLQuickView::consumeCursorDelta()
	{
		QVector2D delta;

	#ifdef WIN32
		POINT pos;
		GetCursorPos(&pos);
		delta = QVector2D(float(pos.x - mLastCursorPos.x), float(pos.y - mLastCursorPos.y));

        mLastCursorPos = Vec2i(pos.x, pos.y);

        return delta;
	#else
        //#error No mouse delta function for this platform.
	#endif
	}


	void OpenGLQuickView::resetCursorPosition()
	{
		if (mCapturesCursor == false)
			return;

	#ifdef WIN32
		SetCursorPos(mouseDeltaOffsetX, mouseDeltaOffsetY);
        mLastCursorPos = Vec2i(mouseDeltaOffsetX, mouseDeltaOffsetY);
	#else
        //#error No mouse delta function for this platform
	#endif
	}
}
