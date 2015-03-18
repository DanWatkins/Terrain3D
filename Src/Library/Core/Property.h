//==================================================================================================================|
// Created 2015.03.18 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _Property_h
#define _Property_h

#include <functional>
#include "PropertySignal.h"

template<typename T>
class Property
{
public:
	using SetFunction = std::function<void(T)>;
	using GetFunction = std::function<T(void)>;

public:
	Property<T>()
	{
	}


	Property<T>(SetFunction setFunction, GetFunction getFunction) :
		mSetFunction(setFunction),
		mGetFunction(getFunction)
	{
	}


	Property<T>(const T &other)
	{
		_value = other;
	}


	Property<T>& operator =(const T &rhs)
	{
		mSetFunction(rhs);

		//TODO possible performance hit since we aren't checking if the value actually changed
		mPropertySignal.sendEmit();

		return *this;
	}


	operator T() const
	{
		return _value;
	}


	void connectToOnChanged(std::function<void(void)> observerFunction)
	{
		mPropertySignal.connectToOnChanged(observerFunction);
	}


	T _value;

private:
	SetFunction mSetFunction = [this](T value) { this->_value = value; };
	GetFunction mGetFunction = [this](void)->T { return this->_value; };

	PropertySignal mPropertySignal;
};

#endif
