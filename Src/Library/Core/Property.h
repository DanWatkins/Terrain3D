//==================================================================================================================|
// Created 2015.03.18 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _Property_h
#define _Property_h

#include <functional>
#include <QtCore/QVariant>
#include "PropertySignal.h"

template<typename T>
class Property
{
public:
	using SetFunction = std::function<void(const T&)>;
	using GetFunction = std::function<T&(void)>;

public:
	Property<T>()
	{
	}


	Property<T>(const Property<T> &rhs) = delete;


	explicit Property<T>(const SetFunction &setFunction) :
		mSetFunction(setFunction)
	{
	}


	explicit Property<T>(const GetFunction &getFunction) :
		mGetFunction(getFunction)
	{
	}


	Property<T>(const SetFunction &setFunction, const GetFunction &getFunction) :
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


	T &operator()() { return mGetFunction(); }
	const T &operator()() const { return mGetFunction(); }	//TODO careful with returning references
	operator const T&() const { return mGetFunction(); }

	Property<T>& operator +=(const T& rhs) { mSetFunction(_value + rhs); return *this; }
	Property<T>& operator -=(const T& rhs) { mSetFunction(_value - rhs); return *this; }
	
	T operator -() const { return T(-_value); }

	operator QVariant() const { return QVariant(_value); }


	void connectToOnChanged(std::function<void(void)> observerFunction)
	{
		mPropertySignal.connectToOnChanged(observerFunction);
	}


	T _value;

private:
	SetFunction mSetFunction = [this](const T &value) { this->_value = value; };
	GetFunction mGetFunction = [this](void)->T& { return this->_value; };

	PropertySignal mPropertySignal;
};


template <typename T>
bool operator ==(const T &lhs, const Property<T> &rhs) { return lhs == rhs._value; }

template <typename T>
bool operator !=(const T &lhs, const Property<T> &rhs) { return lhs != rhs._value; }

template <typename T>
T operator +(const T &lhs, const Property<T> &rhs) { return lhs + rhs._value; }

template <typename T>
T operator -(const T &lhs, const Property<T> &rhs) { return lhs - rhs._value; }


#define PROPERTY_SETFUNC(type, name, setFunction) Property<type> name = Property<type>::SetFunction([this](const type &value) setFunction);
#define PROPERTY_GETFUNC(type, name, getFunction) Property<type> name = Property<type>::GetFunction([this]()->type& getFunction);
#define PROPERTY_SETGETFUNC(type, name, setFunction, getFunction) Property<type> name { Property<type>::SetFunction([this](const type &value) setFunction), Property<type>::GetFunction([this]()->type& getFunction) };

#endif

