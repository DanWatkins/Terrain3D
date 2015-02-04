#ifndef GENERATOR_H
#define GENERATOR_H

#include <World/Terrain/Generator/Generator.h>

namespace t3d { namespace world { namespace terrain { namespace Generator
{
    class FaultFormation : public Generator
    {
    public:
		void generate(Data &terrainData, int size, int numberOfPasses,
					  float smoothing, int seed);
    };
}}}}

#endif
