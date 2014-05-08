//=======================================================================================================================|
// Created 2014.04.29 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

#include "Camera.h"

namespace t3d
{
	void Camera::uploadTerrainData(HeightMap &heightMap)
	{
		glGenVertexArrays(1, &mRenderData.vao_terrain);
		glBindVertexArray(mRenderData.vao_terrain);

		//vertex data
		Uint vbo;
		heightMap.buildVertexData();
		std::vector<Float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Float)*terrainVertexData->size(), &(*terrainVertexData)[0], GL_STATIC_DRAW);


		//index data
		Uint ibo;
		heightMap.buildIndexData();
		std::vector<Uint16> *terrainIndexData = heightMap.getIndexData();
		mRenderData.indexCount = terrainIndexData->size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Uint16)*terrainIndexData->size(), &(*terrainIndexData)[0], GL_STATIC_DRAW);

		int size = sizeof(Uint16)*terrainIndexData->size();

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(HeightMap::PRIMITIVE_RESTART_INDEX);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);	//pos
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(terrainVertexData->size()*2));	//color

		//glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glBindVertexArray(0);
	}
	

	void Camera::init(World *world)
	{
		mWorld = world;
		
		uploadTerrainData(world->getHeightMap());
	}


	void Camera::render()
	{
		glBindVertexArray(mRenderData.vao_terrain);
		glDrawElements(GL_TRIANGLE_STRIP, mRenderData.indexCount, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}
};