//==================================================================================================================|
// Created 2015.01.04 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_FPS_COUNTER_H
#define _t3d_FPS_COUNTER_H

#include "../Library.h"
#include <list>

namespace t3d
{
	class FPSCounter : public QObject
	{
	Q_OBJECT
	Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)

	public:
		class Timer
		{
		public:
			virtual qint64 elapsed() { return mTimer.elapsed(); }
			virtual void start() { mTimer.start(); }

		private:
			QElapsedTimer mTimer;
		};

	public:
		FPSCounter() = delete;
		FPSCounter(qint64 superSampleRate, qint64 subSampleRate,
				   strong<Timer> timer=strong<Timer>(new Timer));

		int fps() const { return round(mFps); }
		void update();

	signals:
		void fpsChanged();

	private:
		void refreshFPS();

	private:
		qint64 mSuperSampleRate, mSubSampleRate;
		float mFps;

		QList<int> mSubList;
		strong<Timer> mTimer;
	};
}

#endif

