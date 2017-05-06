//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Terrain_Data_H
#define _t3d_World_Terrain_Data_H

#include <ValpineBase/Property.h>

#include <Terrain3D/Library.h>
#include <Terrain3D/World/Terrain/HeightMap.h>
#include <Terrain3D/World/Terrain/LightMap.h>

namespace t3d { namespace world { namespace terrain {

class Data : public QObject
{
    Q_OBJECT

public:
    void cleanup() { /*nothing to cleanup*/ }

    void resetHeightMap(HeightMap &heightMap) { mHeightMap = heightMap; emit heightMapChanged(); }	//TODO really need a move constructor there
    const HeightMap& heightMap() const { return mHeightMap; }
    void resetLightMap(LightMap &lightMap) { mLightMap = lightMap; emit lightMapChanged(); }
    const LightMap &lightMap() const { return mLightMap; }

    typedef QMap<float, GLubyte> HeightIndex;
    void computeTextureIndicies(const HeightIndex &heightIndex);

    typedef QVector<GLubyte> TextureIndicies;
    TextureIndicies& textureIndicies() { return mTextureIndicies; }

    vbase::Property<int> pTextureMapResolution;
    vbase::Property<float> pHeightScale;
    vbase::Property<int> pSpanSize;
    vbase::Property<int> pChunkSize;

signals:
    void heightMapChanged();
    void lightMapChanged();

private:
    HeightMap mHeightMap;
    LightMap mLightMap;
    TextureIndicies mTextureIndicies;
};

}}}

#endif
