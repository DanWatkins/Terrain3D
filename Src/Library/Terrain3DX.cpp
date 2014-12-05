#include "Terrain3DX.h"

Terrain3DX::Terrain3DX() :
	OpenGLQuickItem(&mRenderable)
{
}


void Terrain3DX::Renderable::init()
{
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	mObj.load("./Meshes/cube.obj");
}


void Terrain3DX::Renderable::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mObj.render(Mat4(1.0f));
}
