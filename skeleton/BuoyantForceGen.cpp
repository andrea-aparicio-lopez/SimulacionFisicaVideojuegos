#include "BuoyantForceGen.h"
#include "Particle.h"

using namespace physx;

BuoyantForceGen::BuoyantForceGen(PxVec3 pos, float d)
	: ForceGenerator(pos)
	, _d(d)
{

}

BuoyantForceGen::~BuoyantForceGen() {
	ForceGenerator::~ForceGenerator();
}

void BuoyantForceGen::applyForce(Particle* p) {
	float v = p->getVolume();
	float h = p->getPos().y;
	float immersed;

	if (h - p->getBoxDimensions().y > _pos.y)
		immersed = 0.f;
	else if (h + p->getBoxDimensions().y < _pos.y)
		immersed = 1.0;
	else
		immersed = (_pos.y - h) / (2 * p->getBoxDimensions().y) + 0.5;

	PxVec3 f = { 0, _g * _d * immersed * p->getVolume(), 0};
	
	p->addForce(f);
}

void BuoyantForceGen::update(double dt) {

}