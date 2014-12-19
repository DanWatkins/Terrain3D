//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "CameraItem.h"

namespace t3d
{
	World::Camera *theCamera = nullptr;
}

namespace t3d { namespace QuickItems
{
	class CameraItemRenderer : public QQuickFramebufferObject::Renderer
	{
	public:
		CameraItemRenderer()
		{
		}

		void render()
		{
			if (theCamera)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthMask(GL_TRUE);
				glDepthFunc(GL_LEQUAL);

				QSize frameSize = framebufferObject()->size();
				theCamera->resize(frameSize.width(), frameSize.height());	//TODO pass QSize instead

				glClearColor(1.0f, 0.9f, 0.8f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

				//const qreal retinaScale = devicePixelRatio(); TODO
				//glViewport(0, 0, width() * retinaScale, height() * retinaScale);
				glViewport(0, 0, frameSize.width(), frameSize.height());

				theCamera->render();
			}
			else
			{
				glClearColor(1.0f, 0.3f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
			}

			update();
		}

		QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
		{
			QOpenGLFramebufferObjectFormat format;
			format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
			format.setSamples(4);
			return new QOpenGLFramebufferObject(size, format);
		}
	};


	QQuickFramebufferObject::Renderer *CameraItem::createRenderer() const
	{
		return new CameraItemRenderer;
	}
}}
