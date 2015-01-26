//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <iostream>

#include "Environment.h"
#include <World/Terrain/Generator/FaultFormation.h>
#include <World/Terrain/Lighting/Slope.h>

#include <World/Entity/BaseEntity.h>
#include <World/Entity/RenderComponent.h>

namespace t3d { namespace World
{
	Environment::Environment()
	{
	}


	void Environment::init(const Configuration &configuration)
	{
		Terrain::Generator::FaultFormation generator;
		mTerrainData.setTextureMapResolution(configuration.generatorTextureMapResolution);

		int actualSize = configuration.generatorSize+1;
		int actualSeed = (configuration.generatorSeed == 0) ? (int)time(NULL) : configuration.generatorSeed;

		qDebug() << "Generating terrain data...";
		generator.generate(mTerrainData, actualSize,
						   configuration.generatorFaultCount,
						   configuration.generatorSmoothing,
						   actualSeed);
		Terrain::Data::HeightIndex hi;
		hi[0.25f] = 0;
		hi[0.35f] = 1;
		hi[0.75f] = 2;
		hi[1.00f] = 3;
		mTerrainData.computeTextureIndicies(hi);

		mTerrainData.lightMap().reserve(actualSize);
		Terrain::Lighting::Slope::computeBrightness(mTerrainData.lightMap(),
													mTerrainData.heightMap(),
													configuration.generatorLightIntensity);

		mAssetManager.loadMeshesFromDirectory("../Meshes");
		mEntityManager.init(&mAssetManager);

		generateEntities();
	}


	void Environment::generateEntities()
	{
		Terrain::HeightMap &hm = mTerrainData.heightMap();
		const int density = 5;
		const int NumTreesAttempt = (density*hm.size()/64) * (density*hm.size()/64);

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
			int x = randInt(0, hm.size()-1);
			int y = randInt(0, hm.size()-1);

			//is there grass at this texture index?
			int res = mTerrainData.textureMapResolution();
			if (mTerrainData.textureIndicies()[x*res + y*hm.size()*res*res] == 2)
			{
				strong<Entity::BaseEntity> e1 = mEntityManager.createEntity();
				
				float height = hm.get(x, y);
				e1->setPos(Vec3f(x, 30*height, y));	//hardcoded, GROSS TODO

				e1->createRenderComponent();
				QString treeName = treeList[randInt(0, treeList.size()-1)];
				e1->renderComponent()->setMesh(mAssetManager.meshForName(treeName));
			}
		}
	}
}}