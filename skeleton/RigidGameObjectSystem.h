#pragma once
#include "RigidBodySystem.h"

class RigidGameObject;

class RigidGameObjectSystem : public RigidBodySystem
{
public:
	RigidGameObjectSystem(physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	virtual ~RigidGameObjectSystem();

	void addGameObject(RigidGameObject* rigidGO);

	virtual void update(double dt) override;

protected:
	std::list<RigidGameObject*> _gameObjects;
};

