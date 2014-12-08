#include "../OpenGLQuickItem.h"
#include "RenderThread.h"
#include "TextureNode.h"

namespace t3d
{
	QList<OpenGLQuickItem::RenderThread *> OpenGLQuickItem::mThreads;

	OpenGLQuickItem::OpenGLQuickItem() :
		mRenderThread(0)
	{
		setFlag(ItemHasContents, true);
		mRenderThread = new RenderThread(QSize(512, 512), this);
	}


	void OpenGLQuickItem::endAllRenderThreads()
	{
		foreach (RenderThread *t, OpenGLQuickItem::mThreads)
		{
			t->wait();
			delete t;
		}
	}


	void OpenGLQuickItem::enqueue(RenderThread *thread)
	{
		mThreads << thread;
	}


	void OpenGLQuickItem::ready()
	{
		mRenderThread->ready();
		mRenderThread->moveToThread(mRenderThread);
		connect(window(), SIGNAL(sceneGraphInvalidated()), mRenderThread, SLOT(shutDown()), Qt::QueuedConnection);

		mRenderThread->start();
		update();
	}


	QSGNode *OpenGLQuickItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
	{
		TextureNode *node = static_cast<TextureNode *>(oldNode);

		if (!mRenderThread->hasValidContext())
		{
			QOpenGLContext *current = window()->openglContext();
			current->doneCurrent();

			mRenderThread->createContext(current);

			current->makeCurrent(window());

			QMetaObject::invokeMethod(this, "ready");
			return 0;
		}

		if (!node)
		{
			node = new TextureNode(window());

			connect(mRenderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
			connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
			connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
			connect(node, SIGNAL(textureInUse()), mRenderThread, SLOT(renderNext()), Qt::QueuedConnection);

			QMetaObject::invokeMethod(mRenderThread, "renderNext", Qt::QueuedConnection);
		}

		node->setRect(boundingRect());

		return node;
	}
}
