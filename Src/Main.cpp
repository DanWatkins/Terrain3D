//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Main.h"
#include "Terrain3D.h"

using namespace t3d;

int main()
{
	Terrain3D *app = new Terrain3D;
	return app->init(1600, 900, gWindowTitle);
}