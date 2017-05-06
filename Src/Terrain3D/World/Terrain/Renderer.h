//==================================================================================================================|
// Created 2014.10.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_world_Terrain_Renderer_H
#define _t3d_world_Terrain_Renderer_H

#include <ValpineBase/Loadable.h>
#include <ValpineBase/Property.h>

#include <Terrain3D/Library.h>
#include <Terrain3D/Core/ShaderProgram.h>
#include <Terrain3D/World/Terrain/Data.h>
#include <Terrain3D/World/Terrain/Water/Renderer.h>

namespace t3d { namespace world { namespace terrain {

enum class Mode
{
    Normal,
    WireFrame
};

class Renderer : public core::ShaderProgram, public vbase::Loadable
{
    Q_OBJECT

public:
    Renderer();
    ~Renderer() {}

    void init(Data *terrainData);
    void refresh();

    void reloadShaders() override;

    void cleanup();
    void prepareForRendering();
    void render(const Vec3f &cameraPos, const Mat4 &modelViewMatrix, const Mat4 &perspectiveMatrix);

    vbase::Property<float> pLodFactor = 1.0f;
    vbase::Property<float> pLodNear = 50.0f;
    vbase::Property<float> pLodFar = 450.0f;
    vbase::Property<Mode> pMode = Mode::Normal;

protected:
    void addShaders() override;
    void queryUniformLocations() override;
    void refreshUniformValues() override;

private:
    Q_DISABLE_COPY(Renderer)

    Data *mTerrainData;
    water::Renderer mWaterRenderer;

    GLuint mVao;
    GLuint mVbo[2];

    struct
    {
        GLint mvMatrix;
        GLint projMatrix;

        GLint terrainSize;
        GLint chunkSize;
        GLint lodFactor;
        GLint lodNear;
        GLint lodFar;
        GLint cameraPos;
        GLint heightScale;
        GLint spanSize;

        GLint textureMapResolution;
        GLint heightMapSize;
    } mUniforms;

    struct
    {
        GLuint heightMap;
        GLuint lightMap;
        GLuint indicies;
        GLuint terrain;
    } mTextures;

    struct
    {
        bool terrainData = false;
    } mInvalidations;

private:
    void loadTextures();
    void uploadTerrainData();
};

}}}

#endif
