#pragma once
#include "ForceGenerator.h"

class Particle;

class GravityForceGen : public ForceGenerator
{
public:
	GravityForceGen(physx::PxVec3 pos, physx::PxVec3 g = { 0., -10., 0.});
	~GravityForceGen();

	void applyForce(Particle* p) override;

protected:
	physx::PxVec3 _g;
};

