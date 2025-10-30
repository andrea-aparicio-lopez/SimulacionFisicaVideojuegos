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
	p->addForce(p->getMass() * _g);
}