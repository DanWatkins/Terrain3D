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
	static int LOD = 3;


	Camera::Camera(OpenGLWindow *window) :
		mPosition(-10, 100, -10),
		mHorizontalAngle(0.0f),
		mVerticalAngle(0.0f),
		mFieldOfView(50.0f),
		mNearPlane(0.01f),
		mFarPlane(1500),
		mAspectRatio(1), 
		mMaxVerticalAngle(95.0f),
		mProgram(window),
		mSpacing(1.0f),
		mHeightScale(75.0f),
		mBlockSize(8),
		mMode(Mode::Normal)
	{
		lookAt(Vec3f(100, 10, 100));
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

				//compute the index buffer offset and count for rendering
				int startOffset = 0;
				int count = 0;

				for (int i=0; i<mIndexDataList.size(); i++)
				{
					if (LOD == i)
					{
						count = mIndexDataList[i].size();
						break;
					}
					else
					{
						startOffset += mIndexDataList[i].size()*sizeof(GLuint);
					}
				}


				//render all of the blocks
				for (int y=0; y<numberOfBlocksOnASide; y++)
				{
					int offsetY = y * (mBlockSize*numberOfBlocksOnASide + 1)*mBlockSize;

					for (int x=0; x<numberOfBlocksOnASide; x++)
					{
						int offsetX = x*mBlockSize;
						int baseVertex = offsetX+offsetY;

						glUniform2i(mUniforms.blockIndex, x, y);
						glDrawElementsBaseVertex(openglMode, count, GL_UNSIGNED_INT, (void*)startOffset, baseVertex);
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


	void Camera::buildIndexBlock(IndexData &indexData, int heightMapSize, int blockSize)
	{
		int mapSize = ceil(double(heightMapSize-1) / double(mBlockSize));
		int mapSizeVertex = mapSize*mBlockSize + 1;

		indexData.clear();
		indexData.reserve((blockSize+1) * ((blockSize+1)*2 + 1));

		for (int y=0; y<blockSize; y++)
		{
			int scale = mBlockSize / blockSize;
			int offset = y*mapSizeVertex*scale;
			

			for (int x=0; x<blockSize+1; x++)
			{
				indexData.push_back(x*scale + offset);
				indexData.push_back(x*scale + mapSizeVertex*scale + offset);
			}

			indexData.push_back(PrimitiveRestartIndex);
		}
	}


	int maxLevelsOfDetail(int blockSize)
	{
		return 1 + int(std::log10(blockSize)/std::log10(2));
	}


	int sizeForLod(int lod)
	{
		return std::pow(2, lod);
	}


	void Camera::buildIndexData()
	{
		std::cout << "Generating index data set" << std::endl;

		int heightMapSize = mWorld->getHeightMap().getSize();
		int lod = maxLevelsOfDetail(mBlockSize);

		for (int i=0; i<lod; i++)
		{
			mIndexDataList.push_back(IndexData());
			buildIndexBlock(mIndexDataList.back(), heightMapSize, sizeForLod(i));
		}
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

		int reserve = 0;
		for (int i=0; i<mIndexDataList.size(); i++)
			reserve += mIndexDataList[i].size()*sizeof(GLuint);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, reserve, NULL, GL_STATIC_DRAW);

		int previousOffset = 0;
		for (int i=0; i<mIndexDataList.size(); i++)
		{
			IndexData *indexData = &mIndexDataList[i];
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, previousOffset, sizeof(GLuint)*mIndexDataList[LOD].size(), &mIndexDataList[LOD][0]);

			previousOffset += indexData->size() * sizeof(GLuint);
		}

		
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