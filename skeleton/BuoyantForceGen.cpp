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
	float d = p->getBoxDimensions().y / 2;
	float immersed;

	if (h - d > _pos.y)
		immersed = 0.f;
	else if (h + d < _pos.y)
		immersed = 1.f;
	else
		//immersed = (_pos.y - h) / (2 *d);
		immersed = (_pos.y - (h - d)) / (2 * d);

	PxVec3 f = { 0, _g * _d * immersed * p->getVolume(), 0};
	
	p->addForce(f);
}

void BuoyantForceGen::applyForce(PxRigidBody* p) {
}

void BuoyantForceGen::update(double dt) {

}