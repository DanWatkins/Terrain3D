//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _GL_TERRAIN3D_H
#define _GL_TERRAIN3D_H

#include "OpenGLQuickView.h"
#include "BackgroundUpdater.h"
#include "Settings.h"

#include <Application.h>
#include <Core/FPSCounter.h>
#include <World/World.h>
#include <World/Camera.h>
#include "QuickItems/CameraItem.h"

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
		Q_PROPERTY(int fps READ fps NOTIFY fpsChanged);

	public:
		Terrain3D(Settings *mainSettings);
		~Terrain3D();

		/**
		 * @brief
		 */
		void init();


		/**
		 * @returns True if a new instance of Terrain3D should be run after this
		 * one terminates.
		 */
		Q_INVOKABLE bool needsRestart() { return mNeedsRestart; }

		/**
		 * @brief Causes the view to terminate and flag as needing a restart.
		 */
		Q_INVOKABLE void requestRestart() { mNeedsRestart = true; QQuickView::close(); }

		/**
		 *
		 */
		Q_INVOKABLE void toggleCaptureCursor();

		/**
		 *
		 */
		Q_INVOKABLE void toggleFullscreen();


		/**
		 *
		 */
		Q_INVOKABLE void toggleWireframe();


		/**
		 * @see SettingsListener::settingsValueChanged()
		 */
		void settingsValueChanged(Settings::Key key, const QVariant &value);

		int fps() const { return mFPSCounter.fps(); }

	private:
		World::World mWorld;
		weak<World::Camera> mCamera;
		bool mPreviouslyHadFocus;
		bool mNeedsRestart;

		Settings *mMainSettings;
		QuickItems::CameraItem *mCameraItem;
		BackgroundUpdater backgroundUpdater;
		FPSCounter mFPSCounter;

	private:
		void keyPressEvent(QKeyEvent *ev) override;

		void updateCursorPos();
		void loadUserSettings();

		World::Camera::Configuration buildCameraConfiguration();
		World::World::Configuration buildWorldConfiguration();

	signals:
		void toggleSettingsMenu();
		void refreshSettingsMenu();
		void fpsChanged();

	public slots:
		void willUpdate();
		void beforeRendering();
		void onFpsChanged();
	};
}

#endif

