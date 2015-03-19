//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Environment_H
#define _t3d_World_Environment_H

#include <World/Terrain/Data.h>
#include <World/Entity/Manager.h>
#include <Core/Asset/Manager.h>

namespace t3d { namespace world
{
	class Environment : public IRefreshable
	{
	public:
		Environment();
		~Environment() {}

		void init();
		void refresh() override;

		terrain::Data& terrainData() { return mTerrainData; }
		entity::Manager& entityManager() { return mEntityManager; }
		asset::Manager& assetManager() { return mAssetManager; }

		Property<int> pSize = 16;
		Property<int> pFaultCount = 100;
		Property<int> pSeed = 0;
		Property<float> pSmoothing = 0.5f;
		Property<float> pLightIntensity = 16.0f;

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
