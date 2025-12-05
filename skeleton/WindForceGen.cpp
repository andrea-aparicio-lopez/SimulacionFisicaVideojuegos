#include "WindForceGen.h"
#include "Particle.h"
#include <cmath>

using namespace physx;

WindForceGen::WindForceGen(PxVec3 pos, PxVec3 range, PxVec3 v, double k1, double k2)
	: ForceGenerator(pos)
	, _range(range)
	, _v(v)
	, _k1(k1)
	, _k2(k2)
{

}

WindForceGen::~WindForceGen() {
	ForceGenerator::~ForceGenerator();
}

void WindForceGen::applyForce(Particle* p) {
	if (withinRange(p->getPos())) {
		auto diff = _v - p->getVel();
		auto f = _k1 * diff + _k2 * diff.magnitude() * diff;
		p->addForce(f);
	}
}

void WindForceGen::applyForce(PxRigidBody* rb) {
	if (withinRange(rb->getGlobalPose().p)) {
		auto diff = _v - rb->getLinearVelocity();
		auto f = _k1 * diff + _k2 * diff.magnitude() * diff;
		rb->addForce(f);
	}
}

void WindForceGen::update(double dt) {

}

bool WindForceGen::withinRange(PxVec3 const& pos) const {
	return (pos.x > _pos.x - _range.x && pos.x < _pos.x + _range.x)
		&& (pos.y > _pos.y - _range.y && pos.y < _pos.y + _range.y)
		&& (pos.z > _pos.z - _range.z && pos.z < _pos.z + _range.z);
}