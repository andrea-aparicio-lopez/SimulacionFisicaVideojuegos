#include "SpringParticlesForceGen.h"
#include "Particle.h"

using namespace physx;

SpringParticlesForceGen::SpringParticlesForceGen(PxVec3 pos, double k, double l)
	: SpringForceGen(pos, k, l)
	, _p1(nullptr)
	, _p2(nullptr)
{

}

SpringParticlesForceGen::~SpringParticlesForceGen() {
	delete _p1;
	delete _p2;
	SpringForceGen::~SpringForceGen();
}

void SpringParticlesForceGen::applyForce(Particle* p) {
	// Fuerza sobre p1
	if (p == _p1) {
		Vector3 d =p->getPos() - _p2->getPos();
		float delta_x = d.normalize() - _l;
		Vector3 force = -_k * delta_x * d;
		p->addForce(force);
	}
	// Fuerza sobre p2
	else if (p == _p2) {
		Vector3 d = p->getPos() - _p1->getPos();
		float delta_x = d.normalize() - _l;
		Vector3 force = -_k * delta_x * d;
		p->addForce(force);
	}
}

void SpringParticlesForceGen::setParticles(Particle* p1, Particle* p2) {
	if (_p1 != nullptr)
		delete _p1;
	_p1 = p1;

	if (_p2 != nullptr)
		delete _p2;
	_p2 = p2;
}