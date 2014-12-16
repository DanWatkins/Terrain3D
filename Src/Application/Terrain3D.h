//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _GL_TERRAIN3D_H
#define _GL_TERRAIN3D_H

#include "OpenGLQuickView.h"
#include "BackgroundUpdater.h"
#include "Settings.h"

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
	class Terrain3D : public OpenGLQuickView, public SettingsListener
	{
		Q_OBJECT
	private:
		World::World mWorld;
		QWeakPointer<World::Camera> mCamera;
		bool mPreviouslyHadFocus;
		bool mNeedsRestart;

		BackgroundUpdater backgroundUpdater;

	private:
		void updateCursorPos();
		void keyPressEvent(QKeyEvent *ev);

	public:
		Terrain3D() : mPreviouslyHadFocus(false), mNeedsRestart(false) {}
		~Terrain3D();
		void init();

		/**
		 * @returns True if a new instance of Terrain3D should be run after this
		 * one terminates.
		 */
		bool needsRestart() { return mNeedsRestart; }

		/**
		 * @brief Causes the view to terminate and flag as needing a restart.
		 */
		Q_INVOKABLE void restart();

		/**
		 * @see SettingsListener::settingsValueUpdated()
		 */
		void settingsValueUpdated(Settings::Key key,
								  const QVariant &newValue,
								  const QVariant &oldValue);

	public slots:
		void willUpdate();
	};
}

#endif

