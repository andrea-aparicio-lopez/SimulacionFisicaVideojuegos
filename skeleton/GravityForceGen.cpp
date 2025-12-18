#include "GravityForceGen.h"
#include "Particle.h"

using namespace physx;

GravityForceGen::GravityForceGen(PxVec3 pos, PxVec3 g)
	: ForceGenerator(pos)
	, _g(g)
{

}

GravityForceGen::~GravityForceGen() {
	ForceGenerator::~ForceGenerator();
}

void GravityForceGen::applyForce(Particle* p) {
	PxVec3 f = p->getMass() * _g;
	p->addForce(f);
}

void GravityForceGen::applyForce(PxRigidBody* rb) {

}

void GravityForceGen::update(double dt) {

}