#ifndef _OPENGL_QUICK_ITEM_H
#define _OPENGL_QUICK_ITEM_H

#include <QtQuick/QQuickItem>
#include <Core/OpenGLFunctions.h>

namespace t3d
{
	class IOpenGLRenderable
	{
	public:
		virtual void init() = 0;
		virtual void render() = 0;
	};


	class OpenGLQuickItem : public QQuickItem,
							protected IOpenGLRenderable,
							protected OpenGLFunctions
	{
		Q_OBJECT

	private:
		Q_DISABLE_COPY(OpenGLQuickItem)

		class RenderThread;
		class TextureNode;

		RenderThread *mRenderThread;
		static QList<RenderThread*> mThreads;

	public:
		OpenGLQuickItem();

		static void endAllRenderThreads();
		static void enqueue(RenderThread *thread);

	public Q_SLOTS:
		void ready();

	protected:
		QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
	};
}
#endif
