#include "Axis.h"
#include "Particle.h"

#include <PxPhysicsAPI.h>

using namespace physx;

Axis::Axis() {
	Particle* p = new Particle(PxVec3(0), PxVec3(0), PxVec3(0), PxVec4(1), 1.0f);
	_axis.push_back(p);

	p = new Particle({ 25, 0, 0 }, PxVec3(0), PxVec3(0), PxVec4(1, 0, 0, 1), 1.0f);
	_axis.push_back(p);

	p = new Particle({ 0, 25, 0 }, PxVec3(0), PxVec3(0), PxVec4(0, 1, 0, 1), 1.0f);
	p->setSize(1.0f);
	_axis.push_back(p);

	p = new Particle({ 0, 0, 25 }, PxVec3(0), PxVec3(0), PxVec4(0, 0, 1, 1), 1.0f);
	_axis.push_back(p);
}

Axis::~Axis() {
	for (auto a : _axis)
		delete a;
}