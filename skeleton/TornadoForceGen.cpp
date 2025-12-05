#include "TornadoForceGen.h"
#include "Particle.h"

using namespace physx;

TornadoForceGen::TornadoForceGen(PxVec3 pos, PxVec3 axis, double r, double k, double k1, double k2)
	: WindForceGen(pos, PxVec3(r,r,r), PxVec3(0), k1, k2)
	, _axis(axis)
	, _r(r)
	, _k(k)
{
	_axis.normalize();
}

TornadoForceGen::~TornadoForceGen() {
	WindForceGen::~WindForceGen();
}

void TornadoForceGen::applyForce(Particle* p) {
	if (withinRange(p->getPos())) {
		auto v = getVel(p->getPos());
		auto diff = v - p->getVel();
		auto f = _k1 * diff + _k2 * diff.magnitude() * diff;
		p->addForce(f);
	}
}

void TornadoForceGen::applyForce(PxRigidBody* rb) {
	if (withinRange(rb->getGlobalPose().p)) {
		auto v = getVel(rb->getGlobalPose().p);
		auto diff = v - rb->getLinearVelocity();
		auto f = _k1 * diff + _k2 * diff.magnitude() * diff;
		rb->addForce(f);
	}
}

bool TornadoForceGen::withinRange(PxVec3 const& pos) const {
	return (pos - _pos).magnitude() < _r;
}

PxVec3 TornadoForceGen::getVel(PxVec3 const& pos) const {
	auto k = _k * _axis;
	return k.cross(pos - _pos);
}