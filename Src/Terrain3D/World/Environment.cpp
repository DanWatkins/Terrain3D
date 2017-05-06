//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Environment.h"
#include <Terrain3D/World/Terrain/Generator/FaultFormation.h>
#include <Terrain3D/World/Terrain/Lighting/Slope.h>

#include <Terrain3D/World/Entity/BaseEntity.h>
#include <Terrain3D/World/Entity/RenderComponent.h>

namespace t3d { namespace world {

Environment::Environment()
{
    auto setNeedsToRegenerate = [this]() { this->mNeedsToRefresh = true; };
    pSize.addOnChangedListener(setNeedsToRegenerate);
    pFaultCount.addOnChangedListener(setNeedsToRegenerate);
    pSeed.addOnChangedListener(setNeedsToRegenerate);
    pSmoothing.addOnChangedListener(setNeedsToRegenerate);
    pLightIntensity.addOnChangedListener(setNeedsToRegenerate);
}

void Environment::init()
{
    vbase::Loadable::Begin b(this);

    generateTerrain(seedToUse());
    mAssetManager.loadMeshesFromDirectory(gDefaultPathMeshes);
    mEntityManager.init(&mAssetManager);
    generateEntities();
}

void Environment::refresh()
{
    vbase::Loadable::Begin b(this);

    if (mNeedsToRefresh)
    {
        generateTerrain(seedToUse());
        generateEntities();
    }
}

int Environment::seedToUse()
{
    if (pSeed == mLastUsedSeed && mLastUsedSeed > 0)
        return mLastUsedSeed;
    else
        return (0 == pSeed) ? std::max((int)time(NULL), 1) : pSeed();
}

void Environment::generateTerrain(int seed)
{
    terrain::Generator::FaultFormation generator;
    qDebug() << "Generating terrain data...";
    generator.generate(mTerrainData, pSize, pFaultCount, pSmoothing, seed);
    qDebug() << "   Generated height map";

    terrain::Data::HeightIndex hi;
    hi[0.15f] = 0;
    hi[0.35f] = 1;
    hi[0.75f] = 2;
    hi[1.00f] = 3;
    mTerrainData.computeTextureIndicies(hi);
    qDebug() << "   Generated texture indicies";

    //compute lighting
    {
        terrain::LightMap lm;
        lm.reserve(pSize);
        terrain::Lighting::Slope::computeBrightness(lm, mTerrainData.heightMap(), pLightIntensity);
        mTerrainData.resetLightMap(lm);
    }

    qDebug() << "   Generated light map";

    mLastUsedSeed = seed;
}

void Environment::generateEntities()
{
    mEntityManager.clear();

    const terrain::HeightMap &hm = mTerrainData.heightMap();
    const double density = 0.06f;
    const int NumTreesAttempt = density*hm.size() * density*hm.size();

    QVector<QString> treeList;
    treeList.append("Tree_Ash_Medium");
    treeList.append("Tree_Coffee_Large");
    treeList.append("Tree_Coffee_Large");
    treeList.append("Tree_Coffee_Large");
    treeList.append("Tree_Ash_Large");
    treeList.append("Bush_Myrtle_01");

    //randomly place trees on the "grass" areas
    for (int i=0; i<NumTreesAttempt; i++)
    {
        int x = vbase::randInt(0, hm.size()-2);
        int y = vbase::randInt(0, hm.size()-2);

        //is there grass at this texture index?
        int res = mTerrainData.pTextureMapResolution;

        if (mTerrainData.textureIndicies()[x*res + y*hm.size()*res*res] == 2)
        {
            strong<entity::BaseEntity> e1 = mEntityManager.createEntity();

            float height = hm.get(x, y);
            e1->setPos(Vec3f(x, height*mTerrainData.pHeightScale, y));	//hardcoded, GROSS TODO

            e1->createRenderComponent();
            QString treeName = treeList[vbase::randInt(0, treeList.size()-1)];
            e1->renderComponent()->setMesh(mAssetManager.meshForName(treeName));
        }
    }
}

}}
