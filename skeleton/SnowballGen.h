#pragma once
#include "RigidBodyGenerator.h"

class SnowballGen : public RigidBodyGenerator
{
public:
	SnowballGen(RigidBodySystem* sys);
	~SnowballGen();

	virtual void generateRigidBody() override;

protected:
	const float SNOWBALL_MASS = .5f;
	const float SNOWBALL_V_MAGNITUDE = 60.f;
	const physx::PxVec3 SNOWBALL_W = { 0.f, 0.f, 0.f };
};

