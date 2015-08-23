//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Entity_BaseEntity_H
#define _t3d_World_Entity_BaseEntity_H

#include <Terrain3D/Library.h>

namespace t3d { namespace world { namespace entity
{
	class RenderComponent;

	/**
	 * @brief A central aggregate of components that make up a simulatable entity.
	 *
	 * After construction no components exist by default. You can request for comonents to be instantiated internally
	 * by calling the create component associated method. For example: createRenderComponent(). The component can be
	 * accessed by calling renderComponent(). BaseEntity is not responsible for coordinating interactions between
	 * components.
	 *
	 * There is some common state information associated with the entity as a whole stored in BaseEntity.
	 */
	class BaseEntity
	{
	public:
		BaseEntity(int id);
		~BaseEntity();

		int id() const { return mId; }
		void setPos(const Vec3f &pos) { mPos = pos; }
		Vec3f pos() const { return mPos; }

		RenderComponent* renderComponent() const;
		void createRenderComponent();

	private:
		int mId;
		Vec3f mPos;

		unique<RenderComponent> mRenderComponent;
	};
}}}

#endif

