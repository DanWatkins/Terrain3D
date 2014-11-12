#ifndef TERRAINGENERATORTESTS_H
#define TERRAINGENERATORTESTS_H

#include "AutoTest.h"
#include <World/TerrainGenerator.h>

using namespace t3d;

class TerrainGeneratorTests : public QObject
{
    Q_OBJECT

private slots:
    void generate()
    {
        TerrainData td;
        TerrainGenerator tg;
        tg.generate(td, 9, 20, 112233);

        //assert nothing
    }
};

DECLARE_TEST(TerrainGeneratorTests)


#endif // TERRAINGENERATORTESTS_H
