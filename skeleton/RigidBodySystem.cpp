#include "RigidBodySystem.h"
#include "RigidBodyGenerator.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

using namespace physx;

RigidBodySystem::RigidBodySystem(PxScene* gScene, PxPhysics* gPhysics)
	: _gScene(gScene)
	, _gPhysics(gPhysics)
{

}

RigidBodySystem::~RigidBodySystem() {
	for (auto ri : _renderItems)
		ri->release();
		
	for (auto rb : _rbs)
		_gScene->removeActor(*rb);

	for (auto gen : _rbGenerators)
		delete gen;
}

void RigidBodySystem::addRB(physx::PxRigidBody* rb) {
	_rbs.push_back(rb);
}

void RigidBodySystem::addRI(RenderItem* ri) {
	_renderItems.push_back(ri);
}

void RigidBodySystem::addRBGen(RigidBodyGenerator* gen) {
	_rbGenerators.push_back(gen);
}

void RigidBodySystem::addForceGen(ForceGenerator* gen) {
	_forceGenerators.push_back(gen);
}

PxScene* RigidBodySystem::getScene() const {
	return _gScene;
}

PxPhysics* RigidBodySystem::getPhysics() const {
	return _gPhysics;
}

void RigidBodySystem::update(double dt) {
	// crear sólidos 
	for (auto gen : _rbGenerators) {
		if (gen->isActive()) {
			gen->update(dt);
			gen->generateRigidBody();
		}
	}

	// aplicar fuerzas
	for (auto f : _forceGenerators) {
		if (f->isActive()) {
			for (auto rb : _rbs)
				f->applyForce(rb);
		}
	}
}