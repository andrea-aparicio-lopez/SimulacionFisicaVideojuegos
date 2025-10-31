#include "ExplosionForceGen.h"

using namespace physx;

ExplosionForceGen::ExplosionForceGen(PxVec3 pos, double r, double k)
	: ForceGenerator(pos)
	, _r(r)
	, _k(k)
{

}

ExplosionForceGen::~ExplosionForceGen() {
	ForceGenerator::~ForceGenerator();
}

void ExplosionForceGen::applyForce(Particle* p) {
	// TODO
}