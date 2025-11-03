#include "ForceGenerator.h"

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