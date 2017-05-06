//==================================================================================================================|
// Created 2015.01.14 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_RENDERER_H
#define _t3d_RENDERER_H

#include <Terrain3D/Library.h>
#include <Terrain3D/World/Entity/RenderComponent.h>
#include <Terrain3D/World/Entity/Manager.h>

namespace t3d { namespace world { namespace entity {

class Renderer
{
public:
    void setManager(Manager *manager) { mManager = manager; }
    //void renderAll(const Mat4 &cameraMatrix);

    void renderAll(const Mat4 &cameraMatrix)
    {
        if (!mManager)
        {
            qDebug() << "entity::Renderer cannot renderAll because there is no valid entity::Manager connected";
            return;
        }

        auto entityContainer = mManager->entityContainer();
        for (strong<BaseEntity> entity : entityContainer)
        {
            if (RenderComponent *cmp = entity->renderComponent())
                cmp->render(cameraMatrix);
        }
    }

private:
    Manager *mManager;
};

}}}

#endif

