#pragma once

#include <PxPhysicsAPI.h>

class ParticleSystem;
class ParticleGen;
class ForceGenerator;
class Player;
class RenderItem;

class Obstacle
{
public:
	Obstacle(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~Obstacle();

	void update(double dt);

	void explode();

	physx::PxRigidStatic* getActor() { return _actor; } 

protected:
	physx::PxScene* _gScene;

	physx::PxRigidStatic* _actor;
	RenderItem* _renderItem;
	float _halfHeight = 1.5f;

	ParticleSystem* _explSys;
	ParticleGen* _explPartGen;
	ForceGenerator* _explForceGen;

	bool _alive = true;
};

