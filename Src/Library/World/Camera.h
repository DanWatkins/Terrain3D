//==================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Camera_H
#define _t3d_World_Camera_H

#include <Library.h>
#include <World/Environment.h>

#include <World/Terrain/Data.h>
#include <World/Terrain/Renderer.h>
#include <World/Entity/Renderer.h>

#include <Core/Loadable.h> //TODO temp

namespace t3d { namespace world
{
	/**
	 * Represents an all-in-one World instance visualizer. It can move forward/backward and left/right. It can also
	 * rotate up/down and left/right.
	 */
	class Camera : public QObject, protected core::BaseOpenGLFunctions, public core::Loadable
	{
		Q_OBJECT

	public slots:
		/**
		 * @brief Renders everything visible by the camera using the current
		 * OpenGL context.
		 */
		void render();

	signals:
		void finishedRendering();
		void posChanged();

	public:
        Camera();
		~Camera() {}

		/**
		 * @brief Gets the instance ready for rendering.
		 * @param configuration Contains various configuration information
		 */
		void init();
		void refresh();

		/**
		 * Does the heavy lifting loading. Loads large resources from file and uploads data to the GPU.
		 * Must be called after init.
		 */
		void prepareForRendering();

		/**
		 * @brief Deallocates all memory allocated in OpenGL on the GPU.
		 */
		void cleanup();

		/**
		 * @brief Adjusts the aspect ratio according to \p windowWidth and \p windowHeight
		 */
		void resize(unsigned windowWidth, unsigned windowHeight);
		void reloadShaders();
		void setEnvironment(Environment *environment) { mEnvironment = environment; }

		Property<float> pFieldOfView = 50.0f;
		Property<float> pNearPlane = 1.0f;
		Property<float> pFarPlane = 1200.0f;
		Property<float> pAspectRatio = 1.0;
		Property<float> pMaxVerticalAngle = 90.0f;


		Property<Vec3f> pPos;
        Property<Vec2f> pOrientationAngle;
		
		Mat4 orientaion() const;

		void lookAt(Vec3f position);
		Vec3f forward() const;
		Vec3f right() const;
		Vec3f up() const;

		void setMode(terrain::Mode mode) { mTerrainRenderer.pMode = mode; }
		terrain::Mode mode() { return mTerrainRenderer.pMode; }

		terrain::Renderer& terrainRenderer() { return mTerrainRenderer; }

	private:
		Environment *mEnvironment;
		terrain::Renderer mTerrainRenderer;
		entity::Renderer mEntityRenderer;

	private:
		Mat4 totalMatrix() const;
		Mat4 perspectiveMatrix() const;
		Mat4 viewMatrix() const;
		void normalizeAngles();
	};
}}

#endif

