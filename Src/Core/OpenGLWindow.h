//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _OPENGL_WINDOW_H
#define _OPENGL_WINDOW_H

#include "../Main.h"

class OpenGLWindow : public QWindow, protected QOpenGLFunctions_4_3_Core
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

	QVector2D getCursorDelta();
	void resetCursorPosition();

private:
	bool mUpdatePending;
	bool mAnimating;

	QOpenGLContext *mContext;
	QOpenGLPaintDevice *mDevice;
};

#endif
