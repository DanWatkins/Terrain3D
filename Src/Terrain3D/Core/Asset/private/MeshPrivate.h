//==================================================================================================================|
// Created 2015.01.23 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Core_Asset_MeshPrivate_H
#define _t3d_Core_Asset_MeshPrivate_H

#include <Terrain3D/Core/Asset/Mesh.h>
#include <Terrain3D/Library.h>

namespace t3d
{
namespace asset
{

class Mesh::MeshPrivate : protected core::OpenGLFunctions
{
  public:
    friend class OBJ;
    MeshPrivate() = delete;
    MeshPrivate(Mesh *mesh);
    void init();
    bool initWithFile(const QString &filepath);

    void batchRender(const QVector<Mat4> &matricies);

    void setFilepath(const QString &filepath);
    QString filepath() const { return mFilepath; }
    QString containingDirectory() const { return mContainingDirectory; }

    void setName(const QString &name) { mName = name; }
    QString name() const { return mName; }
    void setBaseScale(const Vec3f &baseScale) { mBaseScale = baseScale; }

  protected:
    struct Vertex
    {
        GLfloat values[3];
    };

    static const GLuint PrimitiveRestartIndex;

    class MaterialData;
    class FaceData;
    class SubMesh;

    struct Face
    {
        QVector<int> vertexIndex;
        QVector<int> textureIndex;
        QVector<int> normalIndex;
    };

    QList<strong<MaterialData>> mMaterials;

  private:
    Mesh *mMesh = nullptr; // the host mesh using this
    weak<Mesh> mSphere;

    QString mContainingDirectory;
    QString mFilepath;
    QOpenGLShaderProgram mProgram;

    QString mName;
    Vec3f mBaseScale;

    strong<FaceData> mFaceData;
    QList<strong<SubMesh>> mSubMesh;

    struct Uniforms
    {
        GLuint matrixCamera;
        GLuint matrixModel;
        GLuint indexCount;
    } mUniforms;

    void loadShaders();
    void uploadData();
    void checkForErrors();

    void bindForRender();
    void unbindAfterRender();

  protected:
    void makeSubMesh();
    strong<SubMesh> currentSubMesh();
    void addVertexPosition(const Vertex &vertex);
    void addVertexNormal(const Vertex &normal);
    void addTextureCoordinate(const Vertex &texCoord);
};

typedef Mesh::MeshPrivate mesh_p;

}
}

#endif
