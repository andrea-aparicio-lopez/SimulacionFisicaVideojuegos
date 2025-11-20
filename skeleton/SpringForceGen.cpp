#include "SpringForceGen.h"
#include "Particle.h"

using namespace physx;

SpringForceGen::SpringForceGen(PxVec3 pos, double k, double l)
	: ForceGenerator(pos)
	, _k(k)
	, _l(l)
{

}

SpringForceGen::~SpringForceGen() {
	ForceGenerator::~ForceGenerator();
}

void SpringForceGen::applyForce(Particle* p) {
	Vector3 d = p->getPos() - _pos;
	float delta_x = d.normalize() - _l;
	Vector3 force = -_k * delta_x * d;
	p->addForce(force);
}

void SpringForceGen::update(double dt) {

}