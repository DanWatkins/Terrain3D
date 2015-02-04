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

namespace t3d { namespace World
{
	class Environment
	{
	public:
		struct Configuration
		{
			int generatorSize;
			int generatorTextureMapResolution;
			int generatorFaultCount;
			int generatorSeed;
			float generatorSmoothing;
			float generatorLightIntensity;
		};

	public:
		Environment();
		void init(const Configuration &configuration);

		Terrain::Data& terrainData() { return mTerrainData; }
		Entity::Manager& entityManager() { return mEntityManager; }
		Asset::Manager& assetManager() { return mAssetManager; }


	private:
		void generateEntities();

		Terrain::Data mTerrainData;
		Entity::Manager mEntityManager;
		Asset::Manager mAssetManager;
	};
}}

#endif

