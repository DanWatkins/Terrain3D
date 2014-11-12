#ifndef GENERATOR_H
#define GENERATOR_H

#include <World/TerrainGenerator.h>

namespace t3d
{
    class FaultFormation : public Generator
    {
    public:
        void generate(TerrainData &terrainData, int size, int numberOfPasses, int seed);
    };
}

#endif
