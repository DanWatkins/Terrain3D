#ifndef _TEST_WORLD_TERRAIN_GENERATOR_FAULTFORMATION_H
#define _TEST_WORLD_TERRAIN_GENERATOR_FAULTFORMATION_H

#include "AutoTest.h"
#include <World/Terrain/Generator/Generator.h>

using namespace t3d::World::Terrain::Generator;

class Test_WorldTerrainGeneratorFaultFormation : public QObject
{
	Q_OBJECT

private slots:
	void generate()
	{
		//assert nothing
		QFAIL("Fail 2");
	}
};

DECLARE_TEST(Test_WorldTerrainGeneratorFaultFormation)


#endif
