//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _OPENGL_WINDOW_H
#define _OPENGL_WINDOW_H

#include <Main.h>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
public:
	explicit OpenGLWindow(QWindow *parent = 0);

	virtual void render(QPainter *painter);
	virtual void render();

	virtual void initialize();

	void setAnimating(bool animating);

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent *event);
	void exposeEvent(QExposeEvent *event);

	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

	QVector2D consumeCursorDelta();
	void resetCursorPosition();

	void setCapturesCursor(bool capturesCursor) { mCapturesCursor = capturesCursor; }
	bool capturesCursor() { return mCapturesCursor; }
	bool mouseButtonLeftPressed() { return mMouseButtonLeftPressed; }

private:
	QOpenGLContext *mContext;
	QOpenGLPaintDevice *mDevice;

	bool mUpdatePending;
	bool mAnimating;
	bool mCapturesCursor;
	Vec2i mLastCursorPos;
	bool mMouseButtonLeftPressed;
};

#endif
