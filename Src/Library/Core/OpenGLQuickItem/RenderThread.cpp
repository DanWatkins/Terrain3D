#include "RenderThread.h"
#include "../OpenGLQuickItem.h"

OpenGLQuickItem::RenderThread::RenderThread(const QSize &size, IOpenGLRenderable *renderable) :
	mSurface(nullptr),
	mContext(nullptr),
	mRenderFbo(nullptr),
	mDisplayFbo(nullptr),
	mRenderable(renderable),
	mSize(size)
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

	if (!mRenderFbo)
	{
		QOpenGLFramebufferObjectFormat format;
		format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
		mRenderFbo = new QOpenGLFramebufferObject(mSize, format);
		mDisplayFbo = new QOpenGLFramebufferObject(mSize, format);
		mRenderable->init();
	}

	mRenderFbo->bind();
	glViewport(0, 0, mSize.width(), mSize.height());

	mRenderable->render();
	glFlush();
	mRenderFbo->bindDefault();
	qSwap(mRenderFbo, mDisplayFbo);

	emit textureReady(mDisplayFbo->texture(), mSize);
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
