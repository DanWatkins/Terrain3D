#ifndef TERRAINGENERATORTESTS_H
#define TERRAINGENERATORTESTS_H

#include "AutoTest.h"
#include <World/Terrain/Generator/Generator.h>

using namespace t3d;

class TerrainGeneratorTests : public QObject
{
    Q_OBJECT

private slots:
    void generate()
    {
        //assert nothing
    }
};

DECLARE_TEST(TerrainGeneratorTests)


#endif
