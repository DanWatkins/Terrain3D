//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CAMERA_H
#define _t3d_CAMERA_H

#include <Library.h>
#include <World/Environment.h>

#include <World/Terrain/Data.h>
#include <World/Terrain/Renderer.h>
#include <Core/Mesh/OBJ.h>

namespace t3d { namespace World
{
	/**
	 * Represents an all-in-one World instance visualizer. It uses the style of a first person shooter camera. It can
	 * move forward/backward and left/right. It can also rotate up/down and left/right.
	 */
	class Camera : public QObject, protected OpenGLFunctions 
	{
		Q_OBJECT

	public:
		struct Configuration
		{
			float terrainSpacing;
			float terrainHeightScale;
			int terrainBlockSize;
			int terrainSpanSize;
		};

	public slots:
		/**
		 * @brief Renders everything visible by the camera using the current
		 * OpenGL context.
		 */
		void render();

	signals:
		void finishedRendering();

	public:
		OBJ mObj;

		Camera();

		/**
		 * @brief Gets the instance ready for rendering.
		 * @param configuration Contains various configuration information
		 */
		void init(const Configuration &configuration);

		/**
		 * @brief Deallocates all memory allocated in OpenGL on the GPU.
		 */
		void cleanup();

		/**
		 * @brief Adjusts the aspect ratio according to \p windowWidth and \p windowHeight
		 */
		void resize(unsigned windowWidth, unsigned windowHeight);


		void setEnvironment(Environment *environment) { mEnvironment = environment; }

		void setPosition(Vec3f position) { mPosition = position; }
		void incPosition(Vec3f positionAmount) { mPosition += positionAmount; }
		Vec3f position() const { return mPosition; }

		void setFieldOfView(float fieldOfView) { mFieldOfView = fieldOfView; }
		float fieldOfView() const { return mFieldOfView; }
		void setNearPlane(float nearPlane) { mNearPlane = nearPlane; }
		float nearPlane() const { return mNearPlane; }
		void setFarPlane(float farPlane) { mFarPlane = farPlane; }
		float farPlane() const { return mFarPlane; }

		void incOrientation(float rightAngle, float upAngle);
		Mat4 orientaion() const;
		void setAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; }
		float aspectRatio() { return mAspectRatio; }

		void lookAt(Vec3f position);
		Vec3f forward() const;
		Vec3f right() const;
		Vec3f up() const;

		void setMode(Terrain::Mode mode) { mTerrainRenderer.setMode(mode); }
		Terrain::Mode mode() { return mTerrainRenderer.getMode(); }

	private:
		Environment *mEnvironment;
		Terrain::Renderer mTerrainRenderer;

		Vec3f mPosition;
		float mHorizontalAngle, mVerticalAngle;
		float mFieldOfView;
		float mNearPlane, mFarPlane;
		float mAspectRatio;
		float mMaxVerticalAngle;

	private:
		Mat4 totalMatrix() const;
		Mat4 perspectiveMatrix() const;
		Mat4 viewMatrix() const;
		void normalizeAngles();
	};
}}

#endif

