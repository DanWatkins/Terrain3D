//==================================================================================================================|
// Created 2015.03.29 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef t3d_core_MutexTryLocker_H
#define t3d_core_MutexTryLocker_H

#include <Library.h>

namespace t3d { namespace core
{
	class MutexTryLocker
	{
	public:
		MutexTryLocker() = delete;
		MutexTryLocker(QMutex *mutex) : mMutex(mutex), mIsLocked(mMutex->tryLock()) {}
		~MutexTryLocker() { if (mIsLocked) mMutex->unlock(); }

		bool isLocked() const { return mIsLocked; }

	private:
		Q_DISABLE_COPY(MutexTryLocker)

		QMutex *mMutex;
		bool mIsLocked = false;
	};
}}

#endif
