# Overview

An interactive 3D terrain simulation written in C++ using OpenGL 4 and Qt 5. The main features include:

* Procedurally generated terrain and forests.
* Continuous level of detail: Terrain chunks farther away from the camera are rendered with less detail (triangles).
* Single-plane terrain texture and light mapping.
* Static mesh loading and rendering system.
* Customizable settings menu.
* Qt Quick integration.

# Build Instructions

You will need Qt 5.3+, Visual Studio 2013+, and the Qt Visual Studio plugin. You will also need a graphics card that supports OpenGL 4.2. Simply open the Terrain3D.sln root file in Visual Studio and everything should build right out of the box.

Terrain3D is cross platform, but only a Visual Studio project file is maintained. Someday there will be a CMake script configured so you can easily build with any toolchain.

# Screen Shots

![ScreenShot](./Screenshots/terrain3d_main.png)

Procedurally generated terrain and forest.

![ScreenShot](./Screenshots/terrain3d_clod.png)

Continuous level of detail.

![ScreenShot](./Screenshots/terrain3d_settings.png)

Customizable settings menu.