//=======================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Terrain3D.h"
#include "./Core/Core.h"

std::thread luaBackground;

void initLua()
{
	std::string buffer = "a=10";
	Int error;

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);


	while (buffer != "exit")
	{
		std::cin >> buffer;
		
		error = luaL_loadstring(lua, buffer.c_str()) || lua_pcall(lua, 0, 0, 0);
		
		if (error)
		{
			std::cout << lua_tostring(lua, -1);	
			lua_pop(lua, 1);	
		}
	}
};


namespace t3d
{	
	Terrain3D::Terrain3D()
	{
	}

	
	void Terrain3D::onStartup()
	{
		loadShaders();
	}

	
	void Terrain3D::onUpdate(Double timeSinceStartup)
	{
		printf("Time = %g", timeSinceStartup);

		static const Float clearColor[] = { 1.0f, 1.0f, 0.9f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, clearColor);
	}


	void Terrain3D::onKey(Int key, Int action)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
			{
				terminate();
			}
		}
	}

	
	void Terrain3D::onResize(Int width, Int height)
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}


	void Terrain3D::onTerminate()
	{
		luaBackground.detach();
	}


	void Terrain3D::loadShaders()
	{
		Uint shaders[2];
		shaders[0] = Shader::loadShader(String(gDefaultPathShaders)+"standard.vert", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(String(gDefaultPathShaders)+"standard.frag", GL_FRAGMENT_SHADER);

		mProgram = Shader::linkFromShaders(shaders, 2);
	}
};