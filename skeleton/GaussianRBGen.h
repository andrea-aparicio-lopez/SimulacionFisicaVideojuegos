#pragma once
#include "RigidBodyGenerator.h"

class GaussianRBGen : public RigidBodyGenerator
{
public:
	GaussianRBGen(RigidBodySystem* sys, 
		physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w);

	~GaussianRBGen();

	void generateRigidBody() override;

protected:
	std::normal_distribution<double> _d{ 0,1 };
};

