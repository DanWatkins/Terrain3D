//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Manager.h"
#include "RenderComponent.h"

namespace t3d::world::entity {

Manager::Manager() :
    mIdValueTrack(0)
{
}

void Manager::init(const asset::Manager *assetManager)
{
    mAssetManager = assetManager;
}

strong<BaseEntity> Manager::createEntity()
{
    strong<BaseEntity> newEntity(strong<BaseEntity>(new BaseEntity(++mIdValueTrack)));
    mEntityContainer.append(newEntity);

    return newEntity;
}

strong<BaseEntity> Manager::findEntity(int id)
{
    for (int i=0; i<mEntityContainer.count(); i++)
    {
        if (mEntityContainer[i]->id() == id)
            return mEntityContainer[i];
    }

    return nullptr;
}

}
