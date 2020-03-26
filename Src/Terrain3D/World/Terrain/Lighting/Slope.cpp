//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Terrain3D/World/Terrain/Lighting/Slope.h>
#include <Terrain3D/World/Terrain/LightMap.h>
#include <Terrain3D/World/Terrain/HeightMap.h>

namespace t3d::world::terrain::Lighting {

bool Slope::computeBrightness(LightMap &lm, const HeightMap &hm, float intensity)
{
    //ensure the height map and light map are the same size
    if (lm.size() != hm.size())
        return false;

    for (int y=0; y<lm.size(); y++)
    {
        for (int x=0; x<lm.size(); x++)
        {
            if (y == 0)
            {
                lm.set(x, y, 1.0f);
            }
            else
            {
                float prevHeight = hm.get(x, y-1);
                float curHeight = hm.get(x, y);
                float delta = prevHeight - curHeight;
                float brightness = 1.0f;

                if (delta > 0.0f)
                {
                    brightness = (1-delta) * intensity;
                }

                lm.set(x, y, std::max(std::max(0.0f, brightness), 1.0f));
                //TODO problem here I think
            }
        }
    }

    return true;
}

}
