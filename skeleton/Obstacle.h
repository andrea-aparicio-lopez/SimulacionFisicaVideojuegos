#pragma once

#include "RigidGameObject.h"

class Obstacle : public RigidGameObject
{
public:
	Obstacle(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~Obstacle();

	void explode();

protected:

	float _halfHeight = 1.5f;


};

