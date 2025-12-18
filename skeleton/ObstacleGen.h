#pragma once
#include "RigidBodyGenerator.h"

class ObstacleGen : public RigidBodyGenerator
{
public:
	ObstacleGen(RigidBodySystem* sys);
	~ObstacleGen();

	virtual void generateRigidBody() override;
};

