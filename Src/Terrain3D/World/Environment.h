//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Environment_H
#define _t3d_World_Environment_H

#include <ValpineBase/Loadable.h>
#include <ValpineBase/Property.h>

#include <Terrain3D/World/Terrain/Data.h>
#include <Terrain3D/World/Entity/Manager.h>
#include <Terrain3D/Core/Asset/Manager.h>

namespace t3d { namespace world {

/**
 * \brief Top-level aggregate manager of simulation data.
 */
class Environment : public vbase::Loadable
{
public:
    Environment();
    ~Environment() {}

    void init();
    void refresh();

    /**
     * @returns A reference to the internal terrain::Data instance.
     */
    terrain::Data& terrainData() { return mTerrainData; }

    /**
     * @returns A reference to the internal entity::Manager instance.
     */
    entity::Manager& entityManager() { return mEntityManager; }

    /**
     * @returns A reference to the internal asset::Manager instance.
     */
    asset::Manager& assetManager() { return mAssetManager; }

    /**
     * \brief Length of a side of the terrain grid. World coordinates will be on the
     * range [(0,0,0), (pSize, terrain::Data::pHeightScale, pSize)]
     */
    void setSize(int size)
    {
        mSize = size;
        mNeedsToRefresh = true;
    }

    /**
     * \brief Number of faults to use with the fault-formation terrain generation algorithm
     */
    void setFaultCount(int faultCount)
    {
        mFaultCount = faultCount;
        mNeedsToRefresh = true;
    }

    /**
     * \brief Seed value used to initialize the random number generator for randomly generatin
     * the terrain.
     */
    void setSeed(int seed)
    {
        mSeed = seed;
        mNeedsToRefresh = true;
    }

    /**
     * \brief The intensity used for linear smoothing passes in post-process fault-formation
     * terrain generation.
     */
    void setSmoothing(float smoothing)
    {
        mSmoothing = smoothing;
        mNeedsToRefresh = true;
    }

    /**
     * \brief TODO this is a werid setting. It's kind of backwards.
     */
    void setLightIntensity(float lightIntensity)
    {
        mLightIntensity = lightIntensity;
        mNeedsToRefresh = true;
    }

private:
    int seedToUse();
    void generateTerrain(int seed);
    void generateEntities();

    terrain::Data mTerrainData;
    entity::Manager mEntityManager;
    asset::Manager mAssetManager;

    int mSize = 16;
    int mFaultCount = 100;
    int mSeed = 0;
    float mSmoothing = 0.5f;
    float mLightIntensity = 16.0f;

    bool mNeedsToRefresh = false;
    int mLastUsedSeed = 0;
};

}}

#endif
