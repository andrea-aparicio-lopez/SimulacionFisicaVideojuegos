#pragma once

#include <PxPhysicsAPI.h>

class RenderItem;
class ParticleSystem;
class ParticleGen;
class ForceGenerator;

class RigidGameObject
{
public:
	RigidGameObject();
	virtual ~RigidGameObject();

	virtual void update(double dt);

	physx::PxRigidActor* getActor() { return _actor; }

protected:
	physx::PxRigidActor* _actor;

	RenderItem* _renderItem;

	ParticleSystem* _explSys;
	ParticleGen* _explPartGen;
	ForceGenerator* _explForceGen;

	bool _alive = true;
};

