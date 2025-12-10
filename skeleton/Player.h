#pragma once

#include <PxPhysicsAPI.h>
#include <list>

#include "PlayerSolid.h"

class Particle;
class ParticleGen;
class ParticleSystem;
class Projectile;

class Player
{
public:
	Player(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~Player();

	void update(double dt);
	void handleInput(unsigned char key);

public:
	physx::PxVec3 getPos();
	void setPos(physx::PxVec3 pos);

	float getHeight() const;
	float getHalfHeight() const;

public:
	void shoot();

protected:
	//Particle* _player;
	PlayerSolid _playerActor;
	ParticleGen* _trailGen;
	ParticleSystem* _trailSys;

	std::list<Projectile*> _projectiles;

protected:
	float _halfHeight = 1.f;

};

