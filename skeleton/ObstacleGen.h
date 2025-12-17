#pragma once
#include "RigidBodyGenerator.h"

class ObstacleGen : public RigidBodyGenerator
{
public:
	ObstacleGen(RigidBodySystem* sys);
	~ObstacleGen();

	virtual void generateRigidBody() override;

	//void setPos(physx::PxVec3 pos) override; // TODO: sumar offset del obstaculo concreto, evitar clipping con el suelo
};

