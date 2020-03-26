//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Entity_Manager_H
#define _t3d_World_Entity_Manager_H

#include <Terrain3D/Library.h>
#include <Terrain3D/World/Entity/BaseEntity.h>
#include <Terrain3D/Core/Asset/Manager.h>

namespace t3d::world::entity {

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();

    void init(const asset::Manager *assetManager);

    void clear() { mEntityContainer.clear(); }
    strong<BaseEntity> createEntity();
    strong<BaseEntity> findEntity(int id);

    const QVector<strong<BaseEntity>> &entityContainer() const { return mEntityContainer; }

private:
    QVector<strong<BaseEntity>> mEntityContainer;	//TODO finish ReuseVector and use it here!
    int mIdValueTrack;
    const asset::Manager *mAssetManager;
};

}

#endif

