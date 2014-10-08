//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Camera.h"
#include "../Core/MatrixStack.h"
#include "../Core/Shader.h"
#include "../Core/Image.h"

namespace t3d
{
	Camera::Camera(OpenGLWindow *window) :
		mPosition(-10, 40, -10),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(0.01f),
		mFarPlane(1500),
		mAspectRatio(16/9),
		mProgram(window),
		mSpacing(1.0),
		mHeightScale(20.0f)
	{
		lookAt(Vec3f(30, 5, 30));
	}


	void Camera::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, (String(gDefaultPathShaders) + "camera-vert.glsl").c_str());
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, (String(gDefaultPathShaders) + "camera-frag.glsl").c_str());

		if (mProgram.link() == false)
			printf("Problem linking shaders\n");
		else
			printf("Initialized shaders\n");
	}


	void Camera::uploadTerrainData(HeightMap &heightMap)
	{
		//vertex data
		GLuint vbo;
		heightMap.buildVertexData(mSpacing);
		mProgram.setUniformValue(mRenderData.uloc_spacing, mSpacing);
		mProgram.setUniformValue(mRenderData.uloc_heightScale, mHeightScale);
		const std::vector<float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint size = sizeof(float)*terrainVertexData->size();
		glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);

		//index data
		GLuint ibo;
		heightMap.buildIndexData();
		const std::vector<GLuint> *terrainIndexData = heightMap.getIndexData();
		mRenderData.indexCount = terrainIndexData->size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						sizeof(GLuint)*terrainIndexData->size(),
						&(*terrainIndexData)[0], GL_STATIC_DRAW);


		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(HeightMap::PRIMITIVE_RESTART_INDEX);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);	//pos
	}


	void Camera::loadTextures()
	{
		//grid texture
		/*{
			Image image;
			image.loadFromFile_PNG("grid.png");
		
			glGenTextures(1, &mTexture);
			glBindTexture(GL_TEXTURE_2D, mTexture);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, image.getWidth(), image.getHeight());

			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(),
							GL_RGBA, GL_UNSIGNED_BYTE, &image.getImageData()[0]);
		}*/


		//sand texture
		{
			Image image;
			image.loadFromFile_PNG("./Textures/sand.png");

			glGenTextures(1, &mTextureSand);
			glBindTexture(GL_TEXTURE_2D, mTexture);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, image.getWidth(), image.getHeight());

			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(),
							GL_RGBA, GL_UNSIGNED_BYTE, &image.getImageData()[0]);
		}
	}
	

	void Camera::init(World *world)
	{
		initializeOpenGLFunctions();
		mWorld = world;

		loadShaders();
		
		mProgram.bind();
		{
			mRenderData.uloc_cameraMatrix = mProgram.uniformLocation("cameraMatrix");
			mRenderData.uloc_modelMatrix = mProgram.uniformLocation("modelMatrix");
			mRenderData.uloc_spacing = mProgram.uniformLocation("spacing");
			mRenderData.uloc_heightScale = mProgram.uniformLocation("heightScale");

			mVao.create();
			mVao.bind();
			{
				uploadTerrainData(world->getHeightMap());
				loadTextures();
			}
			mVao.release();
		}
		mProgram.release();
	}



	void Camera::render()
	{
		mProgram.bind();
		{
			glUniformMatrix4fv(mRenderData.uloc_cameraMatrix, 1, GL_FALSE, glm::value_ptr(getTotalMatrix()));
			glUniformMatrix4fv(mRenderData.uloc_modelMatrix, 1, GL_FALSE,
								glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			mVao.bind();
			{
				glDrawElements(GL_TRIANGLE_STRIP, mRenderData.indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
			mVao.release();
		}
		mProgram.release();
	}


	Mat4 Camera::getOrientation() const
	{
		Mat4 orientation;
		orientation = glm::rotate(orientation, mVerticalAngle, Vec3f(1, 0, 0));
		orientation = glm::rotate(orientation, mHorizontalAngle, Vec3f(0, 1, 0));
		return orientation;
	}


	void Camera::incOrientation(float rightAngle, float upAngle)
	{
		mHorizontalAngle += rightAngle;
		mVerticalAngle += upAngle;
		normalizeAngles();
	}


	void Camera::lookAt(Vec3f position)
	{
		if (position == mPosition)
		{
			std::cout << "MEGA ERROR: You are trying to look at your origin" << std::endl;
			return;
		}

		Vec3f direction = glm::normalize(position - mPosition);
		mVerticalAngle = radToDeg(asinf(-direction.y));
		mHorizontalAngle = -radToDeg(atan2f(-direction.x, -direction.z));
		normalizeAngles();
	}


	Vec3f Camera::getForward() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 0, -1, 1));
	}


	Vec3f Camera::getRight() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(1, 0, 0, 1));
	}


	Vec3f Camera::getUp() const
	{
		return Vec3f(glm::inverse(getOrientation()) * Vec4f(0, 1, 0, 1));
	}


	Mat4 Camera::getTotalMatrix() const
	{
		return getPerspectiveMatrix() * getViewMatrix();
	}


	Mat4 Camera::getPerspectiveMatrix() const
	{
		return glm::perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
	}


	Mat4 Camera::getViewMatrix() const
	{
		return getOrientation() * glm::translate(Mat4(), -mPosition);
	}


	void Camera::normalizeAngles()
	{
		mHorizontalAngle = fmodf(mHorizontalAngle, 360.0f);
		if (mHorizontalAngle < 0.0f)
			mHorizontalAngle += 360.0f;

		if (mVerticalAngle > mMaxVerticalAngle)
			mVerticalAngle = mMaxVerticalAngle;
		else if (mVerticalAngle < -mMaxVerticalAngle)
			mVerticalAngle = -mMaxVerticalAngle;
	}
};