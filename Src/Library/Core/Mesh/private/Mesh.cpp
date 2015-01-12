//==================================================================================================================|
// Created 2015.01.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mesh.h"

#include "MaterialData.h"
#include "FaceData.h"
#include "SubMesh.h"

namespace t3d
{
	Mesh::Mesh() :
		mFaceData(new FaceData)
	{
	}

	void Mesh::render(const Mat4 &totalMatrix)
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(totalMatrix));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
							   glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			mFaceData->bind();

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
				material->bind();
				subMesh->render();
			}
		}
		mProgram.release();
	}


	void Mesh::init()
	{
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

	
	void Mesh::loadShaders()
	{
		QOpenGLShader vertexShader(QOpenGLShader::Vertex, nullptr);
		vertexShader.compileSourceFile(gDefaultPathShaders + "mesh-vert.glsl");
		mProgram.addShader(&vertexShader);

		QOpenGLShader fragmentShader(QOpenGLShader::Fragment, nullptr);
		fragmentShader.compileSourceFile(gDefaultPathShaders + "mesh-frag.glsl");
		mProgram.addShader(&fragmentShader);

		if (mProgram.link() == false)
			printf("Problem linking Mesh mesh shadres\n");
		else
			printf("Initialized Mesh mesh shaders\n");
	}


	void Mesh::uploadData()
	{
		checkForErrors();

		mFaceData->uploadData();

		for (strong<MaterialData> material : mMaterials)
			material->uploadMaterialData(mContainingDirectory);

		for (strong<SubMesh> subMesh : mSubMesh)
			subMesh->uploadData();
	}


	void Mesh::checkForErrors()
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
			QString formattedError = mFilepath + QString(" - Error: ") + error;
			qFatal(formattedError.toStdString().c_str());
		}
	}
}