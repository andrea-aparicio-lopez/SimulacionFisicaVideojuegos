#include "ExplosionForceGen.h"
#include "Particle.h"

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
	auto d = p->getPos() - _pos;
	auto r_sqrd = pow(_r, 2);
	if (d.magnitudeSquared() < r_sqrd) {
		p->addForce(_k * d / d.magnitudeSquared());
	}
}