#pragma once

#include <PxPhysicsAPI.h>
#include <list>

#include "PlayerSolid.h"
#include "ForceSystem.h"

class Particle;
class ParticleGen;
class ParticleSystem;
class RigidBodyGen;
class RigidBodySystem;
class Projectile;

class Player
{
public:
	Player(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~Player();

	void update(double dt);
	void handleInput(unsigned char key);

public:
	PlayerSolid& getPlayerSolid() { return _playerSolid; }

	physx::PxVec3 getPos();
	void setPos(physx::PxVec3 pos);

	physx::PxVec3 getBottomPos() const;

	float getHeight() const;
	float getHalfHeight() const;

	bool getCanJump() const;
	void setCanJump(bool v);

public:
	void jump();
	void shoot();

protected:
	PlayerSolid _playerSolid;

	ForceSystem _forceSys;

	ForceGenerator* _jumpImpulseForceGen;

	RigidBodySystem* _playerRBSystem;
	RigidBodySystem* _snowBallRBSystem;

	ParticleGen* _trailGen;
	ParticleSystem* _trailSys;

	std::list<Projectile*> _projectiles;

protected:
	bool _running = false;
	bool _canJump = false;

protected:
	const float _halfHeight = 1.f;

	const physx::PxVec3 RUN_IMPULSE = physx::PxVec3(500,0,0);
	const physx::PxVec3 JUMP_IMPULSE = physx::PxVec3(0,30,0);
};

