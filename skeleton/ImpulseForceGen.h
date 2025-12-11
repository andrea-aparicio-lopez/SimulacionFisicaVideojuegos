#pragma once
#include "ForceGenerator.h"
class ImpulseForceGen : public ForceGenerator
{
public:
	ImpulseForceGen(physx::PxVec3 pos, physx::PxVec3 impulse);
	~ImpulseForceGen();

	virtual void applyForce(Particle* p) override;
	virtual void applyForce(physx::PxRigidBody* rb) override;
	virtual void update(double dt) override;

protected:
	physx::PxVec3 _impulse;
};

