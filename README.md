# Overview

An interactive 3D terrain simulation written in C++ using OpenGL 4 and Qt 5. The main features include:

* Procedurally generated terrain and forests.
* Continuous level of detail: Terrain chunks farther away from the camera are rendered with less detail (triangles). The LODing is done entirely on the GPU using tessellation shaders.
* Single-plane terrain texture and light mapping.
* Static mesh loading and rendering system.
* Simple animated water.
* Customizable settings menu.
* Qt Quick integration.

# Build Instructions

### Requirments

Note: The project may build and run with different configurations. The following are only guarunteed to work.

* **Build Machine**
  * C++ Toolchain: GCC 6.0+ | MSVC 14.0+
  * Qt: 5.9+
* **Target Machine**
  * OS: Windows 7+ | Ubuntu 16.04+
  * OpenGL: 4.3+

### Building

Simply open Terrain3D.qbs in Qt Creator and hit build. When running from the IDE, make sure the working directory is set to &lt;root_path_to_terrain3d&gt;/Deployment/Bin/. Otherwise none of the relative resource paths will work.


# Screen Shots

![ScreenShot](./Screenshots/terrain3d_settings.png)

![ScreenShot](./Screenshots/terrain3d_main.png)

![ScreenShot](./Screenshots/terrain3d_clod.png)
