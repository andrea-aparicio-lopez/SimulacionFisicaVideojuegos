#include "RigidBodySystem.h"
#include "RigidBodyGenerator.h"
#include "ForceGenerator.h"

using namespace physx;

RigidBodySystem::RigidBodySystem()
{

}

RigidBodySystem::~RigidBodySystem() {
	for (auto rb : _rbs)
		rb->getScene()->removeActor(*rb);
		
	for (auto gen : _rbGenerators)
		delete gen;

}

void RigidBodySystem::addRB(physx::PxRigidBody* rb) {
	_rbs.push_back(rb);
}

void RigidBodySystem::addRBGen(RigidBodyGenerator* gen) {
	_rbGenerators.push_back(gen);
}

void RigidBodySystem::addForceGen(ForceGenerator* gen) {
	_forceGenerators.push_back(gen);
}

void RigidBodySystem::update(double dt) {
	// crear particulas 
	for (auto gen : _rbGenerators)
		if (gen->isActive())
			gen->generateRigidBody();

	// aplicar fuerzas y actualizar el generador después
	for (auto f : _forceGenerators) {
		if (f->isActive()) {
			for (auto rb : _rbs)
				f->applyForce(rb);
			//f->update(dt);
		}
	}
}