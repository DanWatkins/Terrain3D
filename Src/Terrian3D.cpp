//=======================================================================================================================|
// Created 2014.04.26 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Terrain3D.h"
#include "./Core/Core.h"

namespace t3d
{	
	Terrain3D::Terrain3D()
	{
	}


	void Terrain3D::loadShaders()
	{
		Uint shaders[2];
		shaders[0] = Shader::loadShader(String(gDefaultPathShaders) + "standard.vert", GL_VERTEX_SHADER);
		shaders[1] = Shader::loadShader(String(gDefaultPathShaders) + "standard.frag", GL_FRAGMENT_SHADER);

		mProgram = Shader::linkFromShaders(shaders, 2);

		//fetch all the uniform locations
		//mUniformLocations.matrix_cameraToClip = glGetUniformLocation(mProgram, "matrix_cameraToClip");
		//mUniformLocations.matrix_modelToWorld = glGetUniformLocation(mProgram, "matrix_modelToWorld");
		//mUniformLocations.matrix_worldToCamera = glGetUniformLocation(mProgram, "matrix_worldToCamera");
	}


	void Terrain3D::onStartup()
	{
		loadShaders();

		glUseProgram(0);


		mWorld.init();
		mCamera.init(mProgram, &mWorld);
	}

	
	void Terrain3D::onUpdate(Double timeSinceStartup)
	{
		static const Float clearColor[] = { 1.0f, 1.0f, 0.9f, 1.0f };
		static const Float one[] { 1.0f };
		glClearBufferfv(GL_COLOR, 0, clearColor);
		glClearBufferfv(GL_DEPTH, 0, one);

		glUseProgram(mProgram);
		mCamera.render();
	}


	void Terrain3D::onKey(Int key, Int action)
	{
		const Float translationSpeed = 0.02f;
		const Float scaleSpeed = 0.01f;
		const Float zoomSpeed = 0.02f;
		const Float rotationSpeed = 0.06f;

		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				terminate(); break;
		}
	}

	
	void Terrain3D::onResize(Int width, Int height)
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}


	void Terrain3D::onTerminate()
	{
	}	
};