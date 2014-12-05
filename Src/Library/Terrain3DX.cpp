#include "Terrain3DX.h"
namespace t3d
{
	Terrain3DX::Terrain3DX() :
		OpenGLQuickItem(&mRenderable)
	{
	}


	void Terrain3DX::Renderable::init()
	{
		initializeOpenGLFunctions();
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


	}


	void Terrain3DX::Renderable::render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

	}
}
