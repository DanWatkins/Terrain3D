#include "TextureNode.h"

namespace t3d
{
	OpenGLQuickItem::TextureNode::TextureNode(QQuickWindow *window) :
		mId(0),
		mSize(0, 0),
		mTexture(0),
		mWindow(window)
	{
		mTexture = mWindow->createTextureFromId(0, QSize(1, 1));
		setTexture(mTexture);
		setFiltering(QSGTexture::Linear);
		setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);
	}


	OpenGLQuickItem::TextureNode::~TextureNode()
	{
		delete mTexture;
	}


	void OpenGLQuickItem::TextureNode::newTexture(int id, const QSize &size)
	{
		mMutex.lock();
		mId = id;
		mSize = size;
		mMutex.unlock();

		emit pendingNewTexture();
	}


	void OpenGLQuickItem::TextureNode::prepareNode()
	{
		mMutex.lock();
		int newId = mId;
		QSize size = mSize;
		mId = 0;
		mMutex.unlock();
		if (newId)
		{
			delete mTexture;
			mTexture = mWindow->createTextureFromId(newId, size);
			setTexture(mTexture);

			emit textureInUse();
		}
	}
}
