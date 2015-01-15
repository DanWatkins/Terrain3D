//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Renderer.h"

namespace t3d { namespace World { namespace Entity
{
	void Renderer::renderAll(const Mat4 &cameraMatrix)
	{
		if (!mManager)
		{
			qDebug() << "Entity::Renderer cannot renderAll because there is no valid Entity::Manager connected";
			return;
		}

		auto entityContainer = mManager->entityContainer();
		for (strong<BaseEntity> entity : entityContainer)
		{
			if (BaseEntity::RenderComponent *cmp = entity->renderComponent())
				cmp->render(cameraMatrix);
		}
	}
}}}