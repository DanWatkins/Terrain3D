//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _MAIN_H
#define _MAIN_H

//Linkage
#define QT_CREATOR 1	//temporary hack

#if _MSC_VER >= 1310
	#pragma once

	#include <Windows.h>

	#ifdef _DEBUG
		#pragma comment (lib, "Qt5Guid.lib")
		#pragma comment (lib, "Qt5Cored.lib")
	#else
		#pragma comment (lib, "Qt5Gui.lib")
		#pragma comment (lib, "Qt5Core.lib")
	#endif
#elif QT_CREATOR
	//Do nothing, linking is set in .pro
#else
	#error "Non Windows toolchain detected"
#endif




#endif

