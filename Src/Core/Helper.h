//=======================================================================================================================|
// Created 2013.11.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#ifndef _t3d_HELPER_H
#define _t3d_HELPER_H

#include "../Main.h"

namespace t3d
{
	const Double PI = 3.141592654;
	const Double TWO_PI = PI * 2.0;
	const Double PI_OVER_TWO = PI / 2.0;
	const Double THREE_PI_OVER_TWO = 3.0 * PI / 2.0;
    const Double PI_OVER_180 = 0.0174532925;
    const Double PI_UNDER_180 = 57.29577951;

	Double toDouble(String text);
    Float toFloat(String text);
    Int toInt(String text);
    Bool toBool(String text);

    Double divideD(Double a, Double b);
    Float divideF(Float a, Float b);
    Int divideI(Int a, Int b);

    Int round(Double n);
    Int round(Float n);
    Int roundUp(Double n);
    Int roundUp(Float n);
    Int roundDown(Double n);
    Int roundDown(Float n);

    Double degToRad(Double deg);
    Float degToRad(Float deg);
    Int degToRad(Int deg);
    Double radToDeg(Double rad);
    Float radToDeg(Float rad);
    Int radToDeg(Int rad);

	Bool isEqual(Float a, Float b);
	Bool isEqual(Double a, Double b);

	Bool randBool();
	Int randInt();
	Int randInt(Int a, Int b);
	Double randFloat();
	Double randFloat(Double a, Double b);
	Double randClamped();
};


#endif

