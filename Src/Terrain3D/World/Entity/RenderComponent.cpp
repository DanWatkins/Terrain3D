//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "RenderComponent.h"
#include <Terrain3D/Core/Asset/Mesh.h>

namespace t3d { namespace world { namespace entity {

RenderComponent::RenderComponent(BaseEntity *baseEntity) :
    Component(baseEntity)
{
}

void RenderComponent::setMesh(weak<asset::Mesh> mesh)
{
    if (mesh.expired())
    {
        qDebug() << "Assigning expired mesh to RenderComponent for entity " << baseEntity()->id();
    }

    mMesh = mesh;
}

void RenderComponent::render(const Mat4 &cameraMatrix)
{
    Mat4 transformation = glm::translate(Mat4(1.0f), baseEntity()->pos());
    mMesh.lock()->queueRender(cameraMatrix * transformation);
}

}}}
