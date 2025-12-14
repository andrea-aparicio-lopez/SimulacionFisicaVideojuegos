#include "ImpulseForceGen.h"
#include "Particle.h"
#include <iostream>

using namespace physx;

ImpulseForceGen::ImpulseForceGen(PxVec3 pos, PxVec3 impulse)
	: ForceGenerator(pos)
	, _impulse(impulse)
{

}

ImpulseForceGen::~ImpulseForceGen() {
	ForceGenerator::~ForceGenerator();
}

void ImpulseForceGen::applyForce(Particle* p) {
	p->addForce(_impulse);
	_active = false;
}

void ImpulseForceGen::applyForce(physx::PxRigidBody* rb) {
	rb->addForce(_impulse);
	_active = false;
}

void ImpulseForceGen::update(double dt) {

}