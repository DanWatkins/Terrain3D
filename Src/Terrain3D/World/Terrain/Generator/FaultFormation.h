#ifndef GENERATOR_H
#define GENERATOR_H

#include <World/Terrain/HeightMap.h>

namespace t3d
{
    class FaultFormation
    {
    public:
        static void generate(HeightMap &heightMap, int size, int numberOfPasses, int seed);
    };
}

#endif
