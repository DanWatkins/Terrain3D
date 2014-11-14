//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Main.h"
#include <Terrain3D.h>

using namespace t3d;

void main2();

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QSurfaceFormat format;
	format.setSamples(16);

	Terrain3D window;
	window.setFormat(format);
	window.resize(1600, 900);
	window.show();

	window.setAnimating(true);

	return app.exec();
}
