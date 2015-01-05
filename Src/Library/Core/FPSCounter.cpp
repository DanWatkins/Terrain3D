//==================================================================================================================|
// Created 2015.01.04 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|
#include "FPSCounter.h"

namespace t3d
{
	FPSCounter::FPSCounter(qint64 superSampleRate, qint64 subSampleRate,
						   strong<Timer> timer) :
		mSuperSampleRate(superSampleRate),
		mSubSampleRate(subSampleRate),
		mFps(0),
		mTimer(timer)
	{
		mSubList.push_back(0);
		mTimer->start();
	}


	void FPSCounter::update()
	{
		mSubList.back()++;

		if (mTimer->elapsed() >= mSubSampleRate)
		{
			refreshFPS();
			mSubList.push_back(0);
			mTimer->start();
			emit fpsChanged();
		}
	}


	void FPSCounter::refreshFPS()
	{
		const int subSamples = std::min(unsigned(mSuperSampleRate/mSubSampleRate), mSubList.size());

		//sum up the relevant sub list frame counts
		mFps = 0;
		int times = 0;

		std::list<int>::reverse_iterator i = mSubList.rbegin();
		while (i != mSubList.rend())
		{
			if (times >= subSamples)
				break;

			times++;
			mFps += *i;
			i++;
		}

		//divide by factor to get back to a 1 second super sample rate
		const float factor = mSuperSampleRate / 1000.0f;
		mFps /= factor;
	}
}
