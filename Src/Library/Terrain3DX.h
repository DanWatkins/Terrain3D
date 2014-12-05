#ifndef TERRAIN3DX_H
#define TERRAIN3DX_H

#include <Core/OpenGLQuickItem.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions_4_2_Compatibility>

#include <Core/OBJ.h>
#include <World/World.h>
#include <World/Camera.h>

namespace t3d
{
	class Terrain3DX : public OpenGLQuickItem
	{
	public:
		Terrain3DX();

	private:
		class Renderable : public IOpenGLRenderable, protected QOpenGLFunctions_4_2_Compatibility
		{
		public:
			void init() override;
			void render() override;

		private:

		} mRenderable;
	};
}

#endif
