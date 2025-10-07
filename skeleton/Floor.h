#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Floor
{
public:
	Floor(physx::PxVec3 pos, physx::PxVec4 color = {.7, .7, .7, 1});
	~Floor();

protected:
	physx::PxTransform* tr;	// posición

	RenderItem* renderItem;

};

