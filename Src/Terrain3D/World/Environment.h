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
	vbase::Property<int> pSize = 16;

	/**
	 * \brief Number of faults to use with the fault-formation terrain generation algorithm
	 */
	vbase::Property<int> pFaultCount = 100;

	/**
	 * \brief Seed value used to initialize the random number generator for randomly generatin
	 * the terrain.
	 */
	vbase::Property<int> pSeed = 0;

	/**
	 * \brief The intensity used for linear smoothing passes in post-process fault-formation
	 * terrain generation.
	 */
	vbase::Property<float> pSmoothing = 0.5f;

	/**
	 * \brief TODO this is a werid setting. It's kind of backwards.
	 */
	vbase::Property<float> pLightIntensity = 16.0f;

private:
	int seedToUse();
	void generateTerrain(int seed);
	void generateEntities();

	terrain::Data mTerrainData;
	entity::Manager mEntityManager;
	asset::Manager mAssetManager;

	bool mNeedsToRefresh = false;
	int mLastUsedSeed = 0;
};

}}

#endif
