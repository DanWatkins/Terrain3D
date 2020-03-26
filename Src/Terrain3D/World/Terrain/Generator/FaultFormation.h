#ifndef GENERATOR_H
#define GENERATOR_H

#include <Terrain3D/World/Terrain/Generator/Generator.h>

namespace t3d::world::terrain::Generator {

class FaultFormation : public Generator
{
public:
    void generate(Data &terrainData, int size, int numberOfPasses, float smoothing, int seed);
};

}

#endif
