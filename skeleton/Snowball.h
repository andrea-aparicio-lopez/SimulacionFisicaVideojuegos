#pragma once

#include "RigidGameObject.h"

class Snowball : public RigidGameObject
{
public:
	Snowball(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos, physx::PxVec3 v);
	~Snowball();

	//void update(double dt) override;
	physx::PxRigidDynamic* getActor() { return static_cast<physx::PxRigidDynamic*>(_actor); }

	void onImpact();

protected:
	//physx::PxRigidDynamic* _actor;
	const float R = 0.5f;
	const physx::PxVec4 COLOR = { 0.9, 0.9, 0.9, 1 };
};

