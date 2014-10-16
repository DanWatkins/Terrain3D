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
		mPosition(-10, 20, -10),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(0.01f),
		mFarPlane(1500),
		mAspectRatio(1), 
		mMaxVerticalAngle(95.0f),
		mProgram(window),
		mSpacing(1.0f),
		mHeightScale(100.0f),
		mBlockSize(16),
		mMode(Mode::Normal)
	{
		lookAt(Vec3f(20, 0, 20));
	}


	void Camera::init(World *world)
	{
		initializeOpenGLFunctions();
		mWorld = world;

		loadShaders();
		
		mProgram.bind();
		{
			mUniforms.matrixCamera = mProgram.uniformLocation("cameraMatrix");
			mUniforms.matrixModel = mProgram.uniformLocation("modelMatrix");
			mUniforms.spacing = mProgram.uniformLocation("spacing");
			mUniforms.heightScale = mProgram.uniformLocation("heightScale");
			mUniforms.blockSize = mProgram.uniformLocation("blockSize");
			mUniforms.blockIndex = mProgram.uniformLocation("blockIndex");

			mVao.create();
			mVao.bind();
			{
				uploadTerrainData();
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
			glUniformMatrix4fv(mUniforms.matrixCamera, 1, GL_FALSE, glm::value_ptr(getTotalMatrix()));
			glUniformMatrix4fv(mUniforms.matrixModel, 1, GL_FALSE,
								glm::value_ptr(glm::rotate(Mat4(), 0.0f, Vec3f(0, 1, 0))));

			mVao.bind();
			{
				int heightMapSize = mWorld->getHeightMap().getSize();
				int numberOfBlocksOnASide = ceil(double(heightMapSize-1) / double(mBlockSize));

				GLenum openglMode;

				switch (mMode)
				{
				case Mode::Normal:
					openglMode = GL_TRIANGLE_STRIP;
					break;

				case Mode::WireFrame:
					openglMode = GL_LINE_STRIP;
					break;
				}

				for (int y=0; y<numberOfBlocksOnASide; y++)
				{
					int offsetY = y * (mBlockSize*numberOfBlocksOnASide + 1)*mBlockSize;

					for (int x=0; x<numberOfBlocksOnASide; x++)
					{
						int offsetX = x*mBlockSize;
						int baseVertex = offsetX+offsetY;

						glUniform2i(mUniforms.blockIndex, x, y);
						glDrawElementsBaseVertex(openglMode, mIndexData.size(),
												 GL_UNSIGNED_INT, 0, baseVertex);
					}
				}
			}
			mVao.release();
		}
		mProgram.release();
	}


	void Camera::resize(unsigned windowWidth, unsigned windowHeight)
	{
		mAspectRatio = (float)windowWidth / (float)windowHeight;
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


	///// PRIVATE

	void Camera::loadShaders()
	{
		mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, (String(gDefaultPathShaders) + "camera-vert.glsl").c_str());
		mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, (String(gDefaultPathShaders) + "camera-frag.glsl").c_str());

		if (mProgram.link() == false)
			printf("Problem linking shaders\n");
		else
			printf("Initialized shaders\n");
	}


	void Camera::loadTextures()
	{
		//sand texture
		{
			Image imageWater;
			imageWater.loadFromFile_PNG("./Textures/water.png");

			Image imageSand;
			imageSand.loadFromFile_PNG("./Textures/sand.png");

			Image imageGrass;
			imageGrass.loadFromFile_PNG("./Textures/grass.png");

			Image imageMountain;
			imageMountain.loadFromFile_PNG("./Textures/mountain.png");

			int imageSize = imageWater.getWidth();	//for now, assume all images are the same width and height

			glGenTextures(1, &mTextureSand);
			glBindTexture(GL_TEXTURE_2D_ARRAY, mTexture);

			int mipLevels = 8;
			glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevels, GL_RGBA8, imageSize, imageSize, 4);

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
							0, 0, 0,
							imageSize, imageSize, 1,
							GL_RGBA, GL_UNSIGNED_BYTE, &imageWater.getImageData()[0]);

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
							0, 0, 1,
							imageSize, imageSize, 1,
							GL_RGBA, GL_UNSIGNED_BYTE, &imageSand.getImageData()[0]);

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
							0, 0, 2,
							imageSize, imageSize, 1,
							GL_RGBA, GL_UNSIGNED_BYTE, &imageGrass.getImageData()[0]);

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
							0, 0, 3,
							imageSize, imageSize, 1,
							GL_RGBA, GL_UNSIGNED_BYTE, &imageMountain.getImageData()[0]);

			glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
			glSamplerParameteri(mTextureSand, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri(mTextureSand, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}


	void Camera::buildIndexData()
	{
		int heightMapSize = mWorld->getHeightMap().getSize();

		int mapSize = ceil(double(heightMapSize-1) / double(mBlockSize));
		int mapSizeVertex = mapSize*mBlockSize + 1;

		mIndexData.clear();
		mIndexData.reserve((mBlockSize+1) * ((mBlockSize+1)*2 + 1));

		for (int y=0; y<mBlockSize; y++)
		{
			int offset = y*mapSizeVertex;

			for (int x=0; x<mBlockSize+1; x++)
			{
				mIndexData.push_back(x+offset);
				mIndexData.push_back(x+mapSizeVertex + offset);
			}

			mIndexData.push_back(PrimitiveRestartIndex);
		}

		std::cout << "Finished generating index data" << std::endl;
	}


	void Camera::uploadTerrainData()
	{
		HeightMap &heightMap = mWorld->getHeightMap();

		//vertex data
		GLuint vbo;
		heightMap.buildVertexData(mSpacing);
		mProgram.setUniformValue(mUniforms.spacing, mSpacing);
		mProgram.setUniformValue(mUniforms.heightScale, mHeightScale);
		mProgram.setUniformValue(mUniforms.blockSize, float(mBlockSize));
		const std::vector<float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLuint size = sizeof(float)*terrainVertexData->size();
		glBufferData(GL_ARRAY_BUFFER, size, &(*terrainVertexData)[0], GL_STATIC_DRAW);

		//index data
		GLuint ibo;
		buildIndexData();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						sizeof(GLuint)*mIndexData.size(),
						&mIndexData[0], GL_STATIC_DRAW);

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(PrimitiveRestartIndex);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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


	Mat4 Camera::getPerspectiveMatrix() const
	{
		return glm::perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
	}


	Mat4 Camera::getViewMatrix() const
	{
		return getOrientation() * glm::translate(Mat4(), -mPosition);
	}


	Mat4 Camera::getTotalMatrix() const
	{
		return getPerspectiveMatrix() * getViewMatrix();
	}
};