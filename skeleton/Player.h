#pragma once

#include <PxPhysicsAPI.h>
#include <list>

class Particle;
class ParticleGen;
class ParticleSystem;
class Projectile;

class Player
{
public:
	Player(physx::PxVec3 pos);
	~Player();

	void update(double dt);
	void handleInput(unsigned char key);

public:
	physx::PxVec3 getPos() const;
	void setPos(physx::PxVec3 pos);

	float getHeight() const;
	float getHalfHeight() const;

public:
	void shoot();

protected:
	Particle* _player;
	ParticleGen* _trailGen;
	ParticleSystem* _trailSys;

	std::list<Projectile*> _projectiles;

protected:
	float _halfHeight = 1.f;

};

