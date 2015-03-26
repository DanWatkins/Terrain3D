//==================================================================================================================|
// Created 2015.03.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _Refreshable_H
#define _Refreshable_H

class Refreshable
{
public:
	virtual ~Refreshable() {}
	virtual void refresh() = 0;
};

#endif
