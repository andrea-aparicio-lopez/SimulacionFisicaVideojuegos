#pragma once

#include <PxPhysicsAPI.h>

class Particle;

class ForceGenerator
{
protected:
	ForceGenerator(physx::PxVec3 pos);

public:
	~ForceGenerator();
	virtual physx::PxVec3 applyForce(Particle* p) = 0;

protected:
	physx::PxVec3 _pos;
};

