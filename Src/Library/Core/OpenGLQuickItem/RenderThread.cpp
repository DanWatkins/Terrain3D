#include <QtGui/QOpenGLFunctions>

#include "RenderThread.h"
#include "../OpenGLQuickItem.h"

namespace t3d
{
	OpenGLQuickItem::RenderThread::RenderThread(const QQuickItem *hostItem, IOpenGLRenderable *renderable) :
		mSurface(nullptr),
		mContext(nullptr),
		mHostItem(hostItem),
		mRenderFbo(nullptr),
		mDisplayFbo(nullptr),
		mRenderable(renderable)
	{
		OpenGLQuickItem::enqueue(this);
	}


	void OpenGLQuickItem::RenderThread::ready()
	{
		mSurface = new QOffscreenSurface();
		mSurface->setFormat(mContext->format());
		mSurface->create();
	}


	void OpenGLQuickItem::RenderThread::createContext(QOpenGLContext *sharedContext)
	{
		mContext = new QOpenGLContext();
		mContext->setFormat(sharedContext->format());
		mContext->setShareContext(sharedContext);
		mContext->create();
		mContext->moveToThread(this);
	}


	void OpenGLQuickItem::RenderThread::renderNext()
	{
		mContext->doneCurrent();
		mContext->makeCurrent(mSurface);

		//was there a resize?
		QSize currentSize(mHostItem->width(), mHostItem->height());
		bool resized = (currentSize != mPreviousSize);

		if (resized || !mRenderFbo)
		{
			bool needsInitAfter = !mRenderFbo;

			QOpenGLFramebufferObjectFormat format;
			format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
			mRenderFbo = new QOpenGLFramebufferObject(currentSize, format);
			mDisplayFbo = new QOpenGLFramebufferObject(currentSize, format);


			if (needsInitAfter)
				mRenderable->init();
		}

		mPreviousSize = currentSize;

		mRenderFbo->bind();
		mContext->functions()->glViewport(0, 0, currentSize.width(), currentSize.height());

		mRenderable->render();
		mContext->functions()->glFlush();
		mRenderFbo->bindDefault();
		qSwap(mRenderFbo, mDisplayFbo);

		emit textureReady(mDisplayFbo->texture(), currentSize);
	}


	void OpenGLQuickItem::RenderThread::shutDown()
	{
		qDebug() << "Shutting Down";

		mContext->makeCurrent(mSurface);
		delete mRenderFbo;
		delete mDisplayFbo;
		mContext->doneCurrent();
		delete mContext;

		mSurface->deleteLater();
		exit();
		moveToThread(QGuiApplication::instance()->thread());
	}
}
