#include "ImpulseForceGen.h"
#include "Particle.h"

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
}

void ImpulseForceGen::applyForce(physx::PxRigidBody* rb) {
	rb->addForce(_impulse);
}

void ImpulseForceGen::update(double dt) {

}