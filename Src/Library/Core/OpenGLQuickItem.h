#ifndef _OPENGL_QUICK_ITEM_H
#define _OPENGL_QUICK_ITEM_H

#include <QQuickItem>

class IOpenGLRenderable
{
public:
	virtual void init() = 0;
	virtual void render() = 0;
};


class OpenGLQuickItem : public QQuickItem
{
    Q_OBJECT

private:
	Q_DISABLE_COPY(OpenGLQuickItem)
	OpenGLQuickItem();

	class RenderThread;
	class TextureNode;

	RenderThread *mRenderThread;
	static QList<RenderThread*> mThreads;

public:
	OpenGLQuickItem(IOpenGLRenderable *renderable);

	static void endAllRenderThreads();
	static void enqueue(RenderThread *thread);

public Q_SLOTS:
    void ready();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif
