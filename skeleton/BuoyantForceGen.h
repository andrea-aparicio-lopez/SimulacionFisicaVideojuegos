#pragma once
#include "ForceGenerator.h"
class BuoyantForceGen : public ForceGenerator
{
public:
	BuoyantForceGen(physx::PxVec3 pos, float d);
	~BuoyantForceGen();

	void applyForce(Particle* p) override;
	void update(double dt) override;

protected:
	float _d;
	float _g = 9.8;
};

