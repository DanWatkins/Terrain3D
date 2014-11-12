#ifndef GENERATOR_H
#define GENERATOR_H

#include <World/Terrain/Generator/Generator.h>

namespace t3d
{
    class FaultFormation : public Generator
    {
    public:
        void generate(TerrainData &terrainData, int size, int numberOfPasses, int seed);
    };
}

#endif
