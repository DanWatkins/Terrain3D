//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "CameraItem.h"

namespace t3d::QuickItems
{
	CameraItem::CameraItem() :
		mIsFrozen(false)
	{
	}

	class CameraItemRenderer : public QQuickFramebufferObject::Renderer
	{
	public:
		CameraItemRenderer(CameraItem *host) : mHost(host) {}

	private:
		CameraItem *mHost = nullptr;

		QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override
		{
			QOpenGLFramebufferObjectFormat format;
			format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
			format.setSamples(4);
			return new QOpenGLFramebufferObject(size, format);
		}

		void render() override
		{
			if (auto camera = mHost->camera().lock())
			{
				if (camera->pHasLoaded)
				{
					camera->resize(framebufferObject()->width(),
								   framebufferObject()->height());
					camera->render();
				}
				else
				{
					auto ctx = QOpenGLContext::currentContext()->functions();
					ctx->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					ctx->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				}
			}

			update();
			mHost->window()->resetOpenGLState();
		}
	};


	QQuickFramebufferObject::Renderer *CameraItem::createRenderer() const
	{
		auto renderer = new CameraItemRenderer(const_cast<CameraItem*>(this));

		return renderer;
	}


	weak<world::Camera> CameraItem::createCamera()
	{
		if (!mCamera)
		{
			mCamera = strong<world::Camera>(new world::Camera);
		}

		return mCamera;
	}


	void CameraItem::cleanup()
	{
		mCamera->cleanup();
	}
}
