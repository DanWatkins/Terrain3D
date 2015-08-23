//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_OpenGLQuickView_H
#define _t3d_OpenGLQuickView_H

#include <Terrain3D/Library.h>
#include <QtQuick/QQuickView>

namespace t3d
{
	class OpenGLQuickView : public QQuickView
	{
	public:
		OpenGLQuickView();

		void mousePressEvent(QMouseEvent *ev);
		void mouseReleaseEvent(QMouseEvent *ev);

		QPoint consumeCursorDelta();
		void resetCursorPosition();

		void setCapturesCursor(bool capturesCursor) { mCapturesCursor = capturesCursor; }
		bool capturesCursor() { return mCapturesCursor; }
		bool mouseButtonLeftPressed() { return mMouseButtonLeftPressed; }

	private:
		bool mCapturesCursor;
		QPoint mLastCursorPos;
		bool mMouseButtonLeftPressed;
	};
}

#endif

