#pragma once

#include <PxPhysicsAPI.h>

class RenderItem;

class GroundSolid
{
public:
	GroundSolid(physx::PxScene* gScene, physx::PxPhysics* gPhysics, 
				physx::PxVec3 pos, physx::PxVec3 h, 
				physx::PxVec4 color = physx::PxVec4(1));
	~GroundSolid();

protected:
	physx::PxRigidStatic* _actor;

	RenderItem* _renderItem;
};

