#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Target
{
public:
	Target(physx::PxVec3 pos, physx::PxVec3 size); 
	~Target();

	inline physx::PxTransform* transform() {
		return tr;
	}

protected:
	physx::PxTransform* tr;	// posición

	RenderItem* renderItem;

};

