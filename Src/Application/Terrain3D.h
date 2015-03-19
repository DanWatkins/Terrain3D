//==================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Terrain3D_H
#define _t3d_Terrain3D_H

#include "OpenGLQuickView.h"
#include "BackgroundUpdater.h"
#include "Settings.h"

#include <Application.h>
#include <Core/FPSCounter.h>
#include <World/Environment.h>
#include <World/Camera.h>
#include "QuickItems/CameraItem.h"

namespace t3d
{
	/**
	 * Represents the main application
	 */
	class Terrain3D : public OpenGLQuickView, public SettingsListener
	{
		Q_OBJECT
		Q_PROPERTY(int fps READ fps NOTIFY fpsChanged);
		Q_PROPERTY(QString cameraPos READ cameraPos NOTIFY cameraPosChanged);

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

		Q_INVOKABLE void reloadShaders() { if (auto camera = mCamera.lock()) camera->reloadShaders(); }

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
		void SettingsListener::settingsValueChanged(Settings::Key key, const QVariant &value) override;


		/**
		 * @see SettingsListener::settingsQueueFinishedApplying()
		 */
		void SettingsListener::settingsQueueFinishedApplying() override;

		/**
		 * @returns the current overall frame rate.
		 */
		int fps() const { return mFPSCounter.fps(); }

		/**
		 * @returns the position of the camera formatted as a string.
		 */
		QString cameraPos() const
		{
			if (auto camera = mCamera.lock())
			{
				return QString().sprintf("(x=%.3f,y=%.3f,z=%.3f)", camera->pPos().x, camera->pPos().y, camera->pPos().z);
			}

			return "Unknown";
		}

	private:
		world::Environment mEnvironment;
		weak<world::Camera> mCamera;
		bool mPreviouslyHadFocus;
		bool mNeedsRestart;

		Settings *mMainSettings;
		QuickItems::CameraItem *mCameraItem;
		BackgroundUpdater backgroundUpdater;
		FPSCounter mFPSCounter;

	private:
		struct MovementKeys
		{
			bool w, a, s, d;
			MovementKeys() { clear(); }
			void clear() { w=a=s=d=false; }
		}mMovementKeys;

		void focusOutEvent(QFocusEvent *ev) override;
		void keyPressEvent(QKeyEvent *ev) override;
		void keyReleaseEvent(QKeyEvent *ev) override;

		void updateCursorPos();
		void loadUserSettings();

	signals:
		void toggleSettingsMenu();
		void refreshSettingsMenu();
		void fpsChanged();
		void cameraPosChanged();

	public slots:
		void willUpdate();
		void beforeRendering();
		void onFpsChanged() { emit fpsChanged(); }
		void onCameraPosChanged() { emit cameraPosChanged(); }
	};
}

#endif

