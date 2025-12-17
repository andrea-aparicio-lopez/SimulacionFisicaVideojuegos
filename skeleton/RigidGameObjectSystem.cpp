#include "RigidGameObjectSystem.h"
#include "RigidGameObject.h"

using namespace physx;

RigidGameObjectSystem::RigidGameObjectSystem(PxScene* gScene, PxPhysics* gPhysics)
	: RigidBodySystem(gScene, gPhysics)
{

}

RigidGameObjectSystem::~RigidGameObjectSystem() {
	for (auto gO : _gameObjects)
		delete gO;
}

void RigidGameObjectSystem::addGameObject(RigidGameObject* gO) {
	_gameObjects.push_back(gO);
}

void RigidGameObjectSystem::update(double dt) {
	for (auto gO : _gameObjects)
		gO->update(dt);

	RigidBodySystem::update(dt);
}