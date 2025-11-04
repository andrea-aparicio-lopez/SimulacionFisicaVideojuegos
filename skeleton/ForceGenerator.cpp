#include "ForceGenerator.h"

using namespace physx;

ForceGenerator::ForceGenerator(physx::PxVec3 pos, bool active) : _pos(pos), _active(active)
{

}

ForceGenerator::~ForceGenerator() {

}

bool ForceGenerator::isActive() const {
	return _active;
}

void ForceGenerator::setActive(bool v) {
	_active = v;
}

void ForceGenerator::setPos(PxVec3 pos) {
	_pos = pos;
}