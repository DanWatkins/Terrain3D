//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _GL_TERRAIN3D_H
#define _GL_TERRAIN3D_H

#include "OpenGLQuickView.h"

#include <Main.h>
#include <World/World.h>
#include <World/Camera.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace t3d
{
	struct UniformLocations
	{
		GLuint matrix_cameraToClip;
		GLuint matrix_modelToWorld;
		GLuint matrix_worldToCamera;
	};


	/**
	 * Represents the main application
	 */
	class Terrain3D : public OpenGLQuickView
	{
	private:
		World::World mWorld;
		std::weak_ptr<World::Camera> mCamera;

		bool mPreviouslyHadFocus;

	private:
		void updateCursorPos();
		void keyPressEvent(QKeyEvent *ev);

	public:
		Terrain3D();
		void init();

	public slots:
		void update();
	};
}

#endif

