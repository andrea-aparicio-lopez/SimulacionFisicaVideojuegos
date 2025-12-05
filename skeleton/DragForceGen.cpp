#include "DragForceGen.h"
#include "Particle.h"

using namespace physx;

DragForceGen::DragForceGen(PxVec3 pos, double u)
	: ForceGenerator(pos)
	, _u(u)
	, _ug(_u*_g)
{

}

void DragForceGen::applyForce(Particle* p) {
	PxVec3 f = _ug * p->getMass() * (-1 * p->getVel().getNormalized());
	p->addForce(f);
}

void DragForceGen::applyForce(PxRigidBody* rb) {

}

void DragForceGen::update(double dt) {

}
