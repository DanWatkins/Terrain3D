//==================================================================================================================|
// Created 2015.01.04 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_FPS_COUNTER_H
#define _t3d_FPS_COUNTER_H

#include "../Main.h"

namespace t3d
{
	class Timer
	{
	public:
		virtual qint64 elapsed()
		{
			return mTimer.elapsed();
		}

		virtual void start()
		{
			mTimer.start();
		}

	private:
		QElapsedTimer mTimer;
	};

	class FPSCounter
	{
	public:
		FPSCounter(qint64 superSampleRate, qint64 subSampleRate,
				   strong<Timer> timer=strong<Timer>(new Timer)) :
			mSuperSampleRate(superSampleRate),
			mSubSampleRate(subSampleRate),
			mFps(0),
			mTimer(timer)
		{
			mSubList.append(0);
		}

		int fps() { return mFps; }

		void update()
		{
			mSubList.last()++;

			if (mTimer->elapsed() >= mSubSampleRate)
			{
				refreshFPS();
				mSubList.append(0);
				mTimer->start();
			}
		}

	private:
		void refreshFPS()
		{
			const int subSamples = std::min(int(mSuperSampleRate/mSubSampleRate), mSubList.size());

			//sum up the relevant sub list frame counts
			mFps = 0;
			int times = 0;

			for (int i : mSubList)
			{
				if (times >= subSamples)
					break;

				times++;
				mFps += i;
			}

			//divide by factor to get back to a 1 second super sample rate
			const float factor = mSuperSampleRate / 1000.0f;
			mFps /= factor;
		}

	private:
		FPSCounter() {}
		qint64 mSuperSampleRate, mSubSampleRate;
		int mFps;

		QList<int> mSubList;
		strong<Timer> mTimer;
	};
}

#endif

