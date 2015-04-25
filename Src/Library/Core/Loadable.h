//==================================================================================================================|
// Created 2015.03.25 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _Loadable_H
#define _Loadable_H

#include <Library.h>

namespace t3d { namespace core
{
	class Loadable
	{
	public:
		virtual ~Loadable() {}
		Property<bool> pIsLoading;

		/**
		 * \brief RAII type for properly setting the pIsLoading property.
		 * Instantiate this with a pointer to the Loadable at the start of any root-level "loading" method. The
		 * pIsLoading property will be set to true upon construction, and fale upon destruction.
		 */
		class Begin
		{
		public:
			Begin() = delete;
			Begin(Loadable *parent) : mParent(parent) { mParent->pIsLoading = true; }
			~Begin() { mParent->pIsLoading = false; }

		private:
			Loadable *mParent = nullptr;
		};
	};
}}

#endif
