//==================================================================================================================|
// Created 2014.11.21 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "NormalMap.h"
#include "HeightMap.h"

namespace t3d::world::terrain {

void NormalMap::generate(const HeightMap &hm)
{
    qDebug() << "Generating normal map...";

    //two normals per quad
    int normalCount = (hm.size()-1) * (hm.size()-1) * 2;
    mNormals.reserve(normalCount);

    for (int y=0; y<hm.size()-1; y++)
    {
        for (int x=0; x<hm.size()-1; x++)
        {
            Vec3f a(0.0f, hm.get(x, y), 0.0f);
            Vec3f b(1.0f, hm.get(x+1, y), 0.0f);
            Vec3f c(0.0f, hm.get(x, y+1), 1.0f);
            Vec3f d(1.0f, hm.get(x+1, y+1), 1.0f);

            //triangle 1
            {
                Vec3f normal = glm::normalize(glm::cross(b-a, c-a));
                mNormals.push_back(normal);
                qDebug() << "normal=" << normal.x << "," << normal.y << "," << normal.z;
            }

            //triangle 2
            {
                Vec3f normal = glm::normalize(glm::cross(c-d, b-d));
                mNormals.push_back(normal);
                qDebug() << "normal=" << normal.x << "," << normal.y << "," << normal.z;
            }
        }
    }
}

}
