//=======================================================================================================================|
// Created 2013.11.19 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Helper.h"

namespace t3d
{
	Double toDouble(const String &text)
    {
        Double n;
		std::stringstream(text) >> n;
        return n;
    }

	
	Float toFloat(const String &text)
    {
        Float n;
		std::stringstream(text) >> n;
        return n;
    }

	
	Int toInt(const String &text)
    {
        Int n;
		std::stringstream(text) >> n;
        return n;
    }

	
	Bool toBool(const String &text)
    {
		if (text == "0")
			return false;

        if (text == "true" || text == "True" || text == "TRUE")
            return true;

		//if (text.IsNumeric())
		//	return true;

        return false;
    }

	
    Double divideD(Double a, Double b)
    {
        if (b != 0.0)
            return a/b;

        return 0.0;
    }

	
    Float divideF(Float a, Float b)
    {
        if (b != 0.0f)
            return a/b;

        return 0.0f;
    }

	
    Int divideI(Int a, Int b)
    {
        if (b == 0)
            return 0;

        return a/b;
	}

	
    Int round(Double n)
    {
        Double result = 0.0;

        //get the decimal part
        Double n2 = n - (Int)n;

        //see if the decimal part is closer to 0 or 1
        if (1.0-n2 <= 0.0+n2)
            result = n+(1.0-n2);
        else if (1.0-n2 > 0.0+n2)
            result = n-n2;

        return (Int)result;
    }


    Int round(Float n)
    {
        return (Int)round((Double)n);
    }


    Int roundUp(Double n)
    {
        return (Int)std::ceil(n);
    }

	
    Int roundUp(Float n)
    {
        return (Int)std::ceil(n);
    }
	

    Int roundDown(Double n)
    {
        return (Int)std::floor(n);
    }

	
    Int roundDown(Float n)
    {
        return (Int)std::floor(n);
    }

	
    Double degToRad(Double deg)
    {
        return deg*PI_OVER_180;
    }

	
    Float degToRad(Float deg)
    {
        return deg*(Float)PI_OVER_180;
    }

	
    Int degToRad(Int deg)
    {
        return round((Double)deg*PI_OVER_180);
    }
	

    Double radToDeg(Double rad)
    {
        return rad*PI_UNDER_180;
	}

	
    Float radToDeg(Float rad)
    {
        return rad*(Float)PI_UNDER_180;
    }


    Int radToDeg(Int rad)
    {
        return round((Double)rad*PI_UNDER_180);
	}

	
	Bool isEqual(Float a, Float b)
	{
		return fabs(a-b) < 1E-12;
		/*if (fabs(a-b) < 1E-12)
			return true;

		return false;*/
	}

	
	Bool isEqual(Double a, Double b)
	{
		return fabs(a-b) < 1E-12;
	}


	Bool randBool()
	{
		return randFloat() > 0.5;
	}


	Int randInt()
	{
		return rand();
	}


	Int randInt(Int a, Int b)
	{
		return rand() % (b-a+1) + a;
	}


	Double randFloat()
	{
		return rand() / (RAND_MAX + 1.0);
	}


	Double randFloat(Double a, Double b)
	{
		return a + randFloat() * (b-a);
	}


	Double randClamped()
	{
		return randFloat() - randFloat();
	}
};