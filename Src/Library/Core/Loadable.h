//==================================================================================================================|
// Created 2015.03.25 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _Loadable_H
#define _Loadable_H

#include <Library.h>
#include <Core/Property.h>	//TODO

namespace t3d { namespace core
{
	class Loadable
	{
	public:
		virtual ~Loadable() {}
		virtual void init() { pIsLoading = true; }
		virtual void reinit() { pIsLoading = true; }
		Property<bool> pIsLoading = false;
	};
}}

#endif
