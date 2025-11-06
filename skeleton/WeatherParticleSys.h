#pragma once
#include <PxPhysicsAPI.h>
#include "ParticleSystem.h"

class Player;

class WeatherParticleSys : public ParticleSystem
{
public:
	WeatherParticleSys(Player* player);
	~WeatherParticleSys();

	virtual void update(double dt) override;

protected:
	Player* _player;

	physx::PxVec3 _offset = { 50,30,0 };
};

