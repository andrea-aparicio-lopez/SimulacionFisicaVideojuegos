#include "Mountain.h"
#include "RenderUtils.hpp"

using namespace physx;

Mountain::Mountain(const PxVec3& position, float height) 
	: _tr(new PxTransform(position, PxQuat(PxPi/4.f, PxVec3(0,0,1)))) 
{
	float l = height / abs(cos(135.f * PxPi / 180.f));
	auto geo = PxBoxGeometry(l, l, DEPTH);
	auto shape = CreateShape(geo);

	_rItem = new RenderItem(shape, _tr, COLOR);
}

Mountain::~Mountain() {
	_rItem->release();
	delete _tr;
}

PxTransform* Mountain::getTr() {
	return _tr;
}
