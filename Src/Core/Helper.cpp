//=======================================================================================================================|
// Created 2013.11.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Helper.h"

namespace t3d
{
	double toDouble(const String &text)
    {
        double n;
		std::stringstream(text) >> n;
        return n;
    }

	
	float toFloat(const String &text)
    {
        float n;
		std::stringstream(text) >> n;
        return n;
    }

	
	int toInt(const String &text)
    {
        int n;
		std::stringstream(text) >> n;
        return n;
    }

	
	bool toBool(const String &text)
    {
		if (text == "0")
			return false;

        if (text == "true" || text == "True" || text == "TRUE")
            return true;

		//if (text.IsNumeric())
		//	return true;

        return false;
    }

	
    double divideD(double a, double b)
    {
        if (b != 0.0)
            return a/b;

        return 0.0;
    }

	
    float divideF(float a, float b)
    {
        if (b != 0.0f)
            return a/b;

        return 0.0f;
    }

	
    int divideI(int a, int b)
    {
        if (b == 0)
            return 0;

        return a/b;
	}

	
    int round(double n)
    {
        double result = 0.0;

        //get the decimal part
        double n2 = n - (int)n;

        //see if the decimal part is closer to 0 or 1
        if (1.0-n2 <= 0.0+n2)
            result = n+(1.0-n2);
        else if (1.0-n2 > 0.0+n2)
            result = n-n2;

        return (int)result;
    }


    int round(float n)
    {
        return (int)round((double)n);
    }


    int roundUp(double n)
    {
        return (int)std::ceil(n);
    }

	
    int roundUp(float n)
    {
        return (int)std::ceil(n);
    }
	

    int roundDown(double n)
    {
        return (int)std::floor(n);
    }

	
    int roundDown(float n)
    {
        return (int)std::floor(n);
    }

	
    double degToRad(double deg)
    {
        return deg*PI_OVER_180;
    }

	
    float degToRad(float deg)
    {
        return deg*(float)PI_OVER_180;
    }

	
    int degToRad(int deg)
    {
        return round((double)deg*PI_OVER_180);
    }
	

    double radToDeg(double rad)
    {
        return rad*PI_UNDER_180;
	}

	
    float radToDeg(float rad)
    {
        return rad*(float)PI_UNDER_180;
    }


    int radToDeg(int rad)
    {
        return round((double)rad*PI_UNDER_180);
	}

	
	bool isEqual(float a, float b)
	{
		return fabs(a-b) < 1E-12;
		/*if (fabs(a-b) < 1E-12)
			return true;

		return false;*/
	}

	
	bool isEqual(double a, double b)
	{
		return fabs(a-b) < 1E-12;
	}


	bool randBool()
	{
		return randFloat() > 0.5;
	}


	int randInt()
	{
		return rand();
	}


	int randInt(int a, int b)
	{
		return rand() % (b-a+1) + a;
	}


	double randFloat()
	{
		return rand() / (RAND_MAX + 1.0);
	}


	double randFloat(double a, double b)
	{
		return a + randFloat() * (b-a);
	}


	double randClamped()
	{
		return randFloat() - randFloat();
	}
};