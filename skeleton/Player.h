#pragma once

#include <PxPhysicsAPI.h>

#include "Particle.h"

class Player : public Particle
{
public:
	Player(physx::PxVec3 pos);
	~Player();

};

