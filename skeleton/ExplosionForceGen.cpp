#include "ExplosionForceGen.h"
#include "Particle.h"

#include <iostream>

using namespace physx;

ExplosionForceGen::ExplosionForceGen(PxVec3 pos, double r, double k, double t)
	: ForceGenerator(pos, false)
	//, _rMax(r)
	, _r(0.)
	, _k(k)
	, _duration(t)
{

}

ExplosionForceGen::~ExplosionForceGen() {
	ForceGenerator::~ForceGenerator();
}

void ExplosionForceGen::applyForce(Particle* p) {
	auto d = p->getPos() - _pos;
	auto r_sqrd = pow(_r, 2);
	if (d.magnitudeSquared() < r_sqrd) {
		p->addForce(_k * d / d.magnitudeSquared() * _exp);
	}
}

void ExplosionForceGen::update(double dt) {
	_t += dt;
	if (_duration < _t) setActive(false);
	else {
		_exp = exp(-_t / _duration);
		_r += V_EXP * _t;
	}
}

void ExplosionForceGen::setActive(bool v) {
	if (v) {
		_t = 0.;
		_exp = 1.;
		_r = 0.;
	}
	ForceGenerator::setActive(v);
}