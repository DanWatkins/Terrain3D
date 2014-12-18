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

	private:
		World::World mWorld;
		QWeakPointer<World::Camera> mCamera;
		bool mPreviouslyHadFocus;
		bool mNeedsRestart;

		Settings *mMainSettings;
		BackgroundUpdater backgroundUpdater;

	private:
		void keyPressEvent(QKeyEvent *ev) override;

		void updateCursorPos();
		void loadUserSettings();

	signals:
		void toggleSettingsMenu();
		void refreshSettingsMenu();

	public slots:
		void willUpdate();
	};
}

#endif

