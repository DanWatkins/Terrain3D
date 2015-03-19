//==================================================================================================================|
// Created 2015.03.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _IRefreshable_H
#define _IRefreshable_H

class IRefreshable
{
public:
	virtual ~IRefreshable() {}
	virtual void refresh() = 0;
};

#endif
