#include "RigidGameObjectSystem.h"
#include "RigidGameObject.h"

using namespace physx;

RigidGameObjectSystem::RigidGameObjectSystem(PxScene* gScene, PxPhysics* gPhysics)
	: RigidBodySystem(gScene, gPhysics)
{
	PxU32 nbActors = 50;     // Max number of actors expected in the aggregate
	bool selfCollisions = false;
	_aggregate = gPhysics->createAggregate(nbActors, selfCollisions);

	_gScene->addAggregate(*_aggregate);
}

RigidGameObjectSystem::~RigidGameObjectSystem() {
	_gScene->removeAggregate(*_aggregate);

	for (auto gO : _gameObjects)
		delete gO;

	_aggregate->release();
}

void RigidGameObjectSystem::addGameObject(RigidGameObject* gO) {
	_aggregate->addActor(*gO->getActor());
	_gameObjects.push_back(gO);
}

void RigidGameObjectSystem::update(double dt) {
	for (auto gO : _gameObjects)
		gO->update(dt);

	RigidBodySystem::update(dt);
}