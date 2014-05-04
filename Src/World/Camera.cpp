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
		//vertex data
		Uint vbo;
		heightMap.buildVertexData();
		std::vector<Float> *terrainVertexData = heightMap.getVertexData();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Float)*terrainVertexData->size(), terrainVertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//index data
		Uint ibo;
		heightMap.buildIndexData();
		std::vector<Int> *terrainIndexData = heightMap.getIndexData();
		mRenderData.indexCount = terrainIndexData->size();

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Int)*terrainIndexData->size(), terrainIndexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		//vertex array
		glGenVertexArrays(1, &mRenderData.vao_terrain);
		glBindVertexArray(mRenderData.vao_terrain);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	//pos
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(terrainVertexData->size()*2));	//color
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glEnable(GL_PRIMITIVE_RESTART);

		glBindVertexArray(0);
	}


	void Camera::init(World *world)
	{
		mWorld = world;
		
		uploadTerrainData(world->getHeightMap());
	}


	void Camera::render()
	{
		glPrimitiveRestartIndex(HeightMap::PRIMITIVE_RESTART_INDEX);

		glDrawElements(GL_TRIANGLE_STRIP, mRenderData.indexCount, GL_INT, 0);
	}
};