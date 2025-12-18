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
//class Projectile;
class SnowballSystem;

class Player
{
public:
	Player(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~Player();

	void update(double dt);

public:
	PlayerSolid& getPlayerSolid() { return _playerSolid; }

	physx::PxVec3 getPos();
	void setPos(physx::PxVec3 pos);

	physx::PxVec3 getBottomPos() const;

	float getHeight() const;
	float getHalfHeight() const;

	bool getCanJump() const;
	void setCanJump(bool v);

	bool getRunning() const;
	//void setRunning(bool v);

	void startRun();
	void endRun();
	void onGroundContact();

public:
	void jump();
	void shoot();

protected:
	PlayerSolid _playerSolid;

	ForceSystem _forceSys;

	ForceGenerator* _jumpImpulseForceGen;

	RigidBodySystem* _playerRBSystem;
	SnowballSystem* _snowballSystem;

	ParticleGen* _trailGen;
	ParticleSystem* _trailSys;

	ParticleSystem* _scarf;
	Particle* _scarfAnchor;
	ForceGenerator* _scarfWind;

protected:
	bool _running = false;
	bool _canJump = false;
	double _jumpTimer = 0.;

protected:
	const float _halfHeight = 1.f;

	const physx::PxVec3 JUMP_IMPULSE = physx::PxVec3(0,10000,0);
	const double JUMP_TIMER = 1.;
};

