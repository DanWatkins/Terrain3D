//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OpenGLQuickView.h"

namespace t3d
{
	OpenGLQuickView::OpenGLQuickView() :
		mCapturesCursor(false),
		mMouseButtonLeftPressed(false)
	{
	}


    void OpenGLQuickView::mouseMoveEvent(QMouseEvent *ev)
    {
        mCachedCursorPos = Vec2i(ev->x(), ev->y());
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

        delta = QVector2D(float(mCachedCursorPos.x - mLastCursorPos.x),
                          float(mCachedCursorPos.y - mLastCursorPos.y));

        mLastCursorPos = Vec2i(mCachedCursorPos.x, mCachedCursorPos.y);

        return delta;
	}


	void OpenGLQuickView::resetCursorPosition()
	{
		if (mCapturesCursor == false)
			return;

        QCursor::setPos(QWindow::mapToGlobal(QPoint(mouseDeltaOffsetX, mouseDeltaOffsetY)));
        mLastCursorPos = Vec2i(mouseDeltaOffsetX, mouseDeltaOffsetY);
        mCachedCursorPos = mLastCursorPos;
	}
}
