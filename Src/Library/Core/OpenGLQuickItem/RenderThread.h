#ifndef _RENDER_THREAD_H
#define _RENDER_THREAD_H

#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>

#include <QtCore/QThread>
#include <QtCore/QMutex>

#include <QtGui/QGuiApplication>

#include "../OpenGLQuickItem.h"

namespace t3d
{
	/*
	 * The render thread shares a context with the scene graph and will
	 * render into two separate FBOs, one to use for display and one
	 * to use for rendering
	 */
	class OpenGLQuickItem::RenderThread : public QThread
	{
		Q_OBJECT
	public:
		RenderThread(const QSize &size, IOpenGLRenderable *renderable);

		void ready();
		void createContext(QOpenGLContext *sharedContext);

		bool hasValidContext() { return mContext != nullptr; }

	public slots:
		void renderNext();
		void shutDown();

	signals:
		void textureReady(int id, const QSize &size);

	private:
		Q_DISABLE_COPY(RenderThread)
		RenderThread();

		QOffscreenSurface *mSurface;
		QOpenGLContext *mContext;


		QOpenGLFramebufferObject *mRenderFbo;
		QOpenGLFramebufferObject *mDisplayFbo;

		IOpenGLRenderable *mRenderable;
		QSize mSize;
	};
}

#endif
