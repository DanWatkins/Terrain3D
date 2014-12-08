#ifndef _TEXTURE_NODE_H
#define _TEXTURE_NODE_H

#include <qsgsimpletexturenode.h>
#include <QtQuick/QQuickWindow>
#include <QtCore/QMutex>

#include "../OpenGLQuickItem.h"

namespace t3d
{
	class OpenGLQuickItem::TextureNode : public QObject, public QSGSimpleTextureNode
	{
		Q_OBJECT

	public:
		TextureNode(QQuickWindow *window);
		~TextureNode();

	signals:
		void textureInUse();
		void pendingNewTexture();

	public slots:
		void newTexture(int id, const QSize &size);
		void prepareNode();

	private:

		int mId;
		QSize mSize;

		QMutex mMutex;

		QSGTexture *mTexture;
		QQuickWindow *mWindow;
	};
}

#endif
