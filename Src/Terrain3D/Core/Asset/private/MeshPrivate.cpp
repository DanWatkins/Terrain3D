//==================================================================================================================|
// Created 2015.01.22 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "MeshPrivate.h"
#include "SubMesh.h"
#include "FaceData.h"
#include "MaterialData.h"
#include "OBJ.h"

namespace t3d { namespace asset {

const GLuint mesh_p::PrimitiveRestartIndex = 900000000;

mesh_p::MeshPrivate(Mesh *mesh) : mMesh(mesh), mFaceData(new FaceData)
{
}

void mesh_p::batchRender(const QVector<Mat4> &matricies)
{
    bindForRender();

    for (strong<SubMesh> subMesh : mSubMesh)
    {
        //find the material associated with this sub mesh
        strong<MaterialData> material;
        for (strong<MaterialData> m : mMaterials)
        {
            if (m->mName == subMesh->mMaterial)
            {
                material = m;
                break;
            }
        }

        glUniform1i(mUniforms.indexCount, subMesh->mIndexCount);
        if (material) material->bind();
        subMesh->bind();

        for (const Mat4 &mat : matricies)
        {
            Mat4 resultMatrix = mat * glm::scale(Mat4(1.0f), mBaseScale);

            glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(resultMatrix));
            glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
                               glm::value_ptr(glm::rotate(Mat4(1.0f), 0.0f, Vec3f(0, 1, 0))));


            subMesh->render();
        }

        subMesh->unbind();
        if (material) material->release();
    }

    unbindAfterRender();
}

void mesh_p::init()
{
    initializeOpenGLFunctions();


    loadShaders();
    mProgram.bind();
    {
        mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
        mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
        mUniforms.indexCount = mProgram.uniformLocation("indexCount");

        uploadData();

        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(PrimitiveRestartIndex);
    }

    mProgram.release();
}

bool mesh_p::initWithFile(const QString &filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    //read values from the JSON T3D file
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject object = doc.object();
    {
        setName(object["name"].toString());
        QJsonArray scale = object["baseScale"].toArray();
        setBaseScale(Vec3f(scale[0].toDouble(), scale[1].toDouble(), scale[2].toDouble()));
        QJsonObject boundingSphere = object["boundingSphere"].toObject();
        mMesh->boundingSphere().radius = boundingSphere["radius"].toDouble();
        QJsonArray bsOffset = boundingSphere["offset"].toArray();
        mMesh->boundingSphere().offset = Vec3f(bsOffset[0].toDouble(), bsOffset[1].toDouble(), bsOffset[2].toDouble());
    }

    return OBJ().initWithFile(QFileInfo(filepath).absolutePath() + "/" + object["meshFile"].toString(), this);
}

void mesh_p::setFilepath(const QString &filepath)
{
    mFilepath = filepath;
    mContainingDirectory = QFileInfo(filepath).absolutePath() + "/";
}

void mesh_p::makeSubMesh()
{
    mSubMesh.append(strong<SubMesh>(new SubMesh));
}

strong<mesh_p::SubMesh> mesh_p::currentSubMesh()
{
    return mSubMesh.last();
}

void mesh_p::addVertexPosition(const mesh_p::Vertex &vertex)
{
    mFaceData->mVertecies.push_back(vertex);
}

void mesh_p::addVertexNormal(const mesh_p::Vertex &normal)
{
    mFaceData->mVertexNormals.push_back(normal);
}

void mesh_p::addTextureCoordinate(const mesh_p::Vertex &texCoord)
{
    mFaceData->mTextureCoordinates.push_back(texCoord);
}

void mesh_p::loadShaders()
{
    QString basePath = gDefaultPathShaders + "/mesh/";

    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile(basePath + "mesh.vert.glsl");
    mProgram.addShader(&vertexShader);

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile(basePath + "mesh.frag.glsl");
    mProgram.addShader(&fragmentShader);

    if (mProgram.link() == false)
        qDebug() << "Problem linking Mesh mesh shadres";

    mProgram.bind();

    glUniform1i(mProgram.uniformLocation("vertexPositions"), 2);
    glUniform1i(mProgram.uniformLocation("vertexNormals"), 3);
    glUniform1i(mProgram.uniformLocation("texCoordinates"), 4);
    glUniform1i(mProgram.uniformLocation("material"), 5);

    mProgram.release();

    //TODO swtich this to use the ShaderProgram class
}

void mesh_p::uploadData()
{
    checkForErrors();

    mFaceData->uploadData();

    for (strong<MaterialData> material : mMaterials)
        material->uploadMaterialData(mContainingDirectory);

    for (strong<SubMesh> subMesh : mSubMesh)
        subMesh->uploadData();
}

void mesh_p::checkForErrors()
{
    QString error;

    for (strong<SubMesh> subMesh : mSubMesh)
    {
        subMesh->checkForErrors(mFaceData.get(), error);

        if (!error.isEmpty())
            return;
    }

    if (mFaceData->mVertecies.count() == 0)
        error = QString("No vertex positions defined");
    else if (mFaceData->mVertexNormals.count() == 0)
        error = QString("No vertex normals defined");
    else if (mFaceData->mTextureCoordinates.count() == 0)
        error = QString("No texture coordinates defined");

    if (!error.isEmpty())
    {
        System::fatal(mFilepath + QString(" - Error: ") + error);
    }
}

void mesh_p::bindForRender()
{
    mProgram.bind();
    mFaceData->bind();
}

void mesh_p::unbindAfterRender()
{
    mProgram.release();
}

}}
