#include "ElasticBandForceGen.h"
#include "Particle.h"

using namespace physx;

ElasticBandForceGen::ElasticBandForceGen(PxVec3 pos, double k, double l)
	: SpringParticlesForceGen(pos, k, l)
{

}

ElasticBandForceGen::~ElasticBandForceGen() {
	SpringParticlesForceGen::~SpringParticlesForceGen();
}

void ElasticBandForceGen::applyForce(Particle* p) {
	if ((p == _p1 || p == _p2) &&
		(_p1->getPos() - _p2->getPos()).magnitude() > _l) {

		SpringParticlesForceGen::applyForce(p);
	}
}