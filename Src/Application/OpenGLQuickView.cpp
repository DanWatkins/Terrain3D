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


	QPoint OpenGLQuickView::consumeCursorDelta()
	{
		QPoint currentPos = QCursor::pos();

		QPoint delta = QPoint(float(currentPos.x() - mLastCursorPos.x()),
						  float(currentPos.y() - mLastCursorPos.y()));

		mLastCursorPos = currentPos;

        return delta;
	}


	void OpenGLQuickView::resetCursorPosition()
	{
		if (mCapturesCursor == false)
			return;

		QPoint targetPos = QWindow::framePosition()
						   + QPoint(QWindow::width()/2, QWindow::height()/2);

		QCursor::setPos(targetPos);
		mLastCursorPos = targetPos;
	}
}
