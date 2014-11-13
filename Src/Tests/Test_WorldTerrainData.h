#ifndef _TEST_WORLD_TERRAIN_DATA_H
#define _TEST_WORLD_TERRAIN_DATA_H

#include "AutoTest.h"

#include <World/Terrain/Data.h>

using namespace t3d::World::Terrain;

class Test_WorldTerrainData : public QObject
{
	Q_OBJECT

private slots:
	void computeTextureIndicies1()
	{
		QFAIL("Fail 1");
	}
};

DECLARE_TEST(Test_WorldTerrainData)


#endif
