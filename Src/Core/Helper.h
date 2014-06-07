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
	const double PI = 3.141592654;
	const double TWO_PI = PI * 2.0;
	const double PI_OVER_TWO = PI / 2.0;
	const double THREE_PI_OVER_TWO = 3.0 * PI / 2.0;
    const double PI_OVER_180 = 0.0174532925;
    const double PI_UNDER_180 = 57.29577951;

	double toDouble(const String &text);
	float toFloat(const String &text);
	int toInt(const String &text);
	bool toBool(const String &text);

    double divideD(double a, double b);
    float divideF(float a, float b);
    int divideI(int a, int b);

    int round(double n);
    int round(float n);
    int roundUp(double n);
    int roundUp(float n);
    int roundDown(double n);
    int roundDown(float n);

    double degToRad(double deg);
    float degToRad(float deg);
    int degToRad(int deg);
    double radToDeg(double rad);
    float radToDeg(float rad);
    int radToDeg(int rad);

	bool isEqual(float a, float b);
	bool isEqual(double a, double b);

	bool randBool();
	int randInt();
	int randInt(int a, int b);
	double randFloat();
	double randFloat(double a, double b);
	double randClamped();
};


#endif

