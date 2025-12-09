#include "GaussianRBGen.h"
#include "RigidBodySystem.h"
#include "RenderUtils.hpp"

using namespace physx;

GaussianRBGen::GaussianRBGen(RigidBodySystem* sys,
	physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w)
	: RigidBodyGenerator(sys, pos, m, v, w)
{

}

GaussianRBGen::~GaussianRBGen() {
}

void GaussianRBGen::generateRigidBody() {

	if (_canGenerate) {
		_canGenerate = false;

		// Un poco de aleatoriedad
		PxVec3 pos = _pos + _d(_mt) * _diffPos;
		float m = _m + abs(_d(_mt) * _diffM);
		PxVec3 v = _v + _d(_mt) * _diffV;
		PxVec3 w = _w + _d(_mt) * _diffW;

		PxTransform tr = PxTransform(pos);
		auto rb = _system->getPhysics()->createRigidDynamic(tr);
		rb->setMass(m);
		rb->setLinearVelocity(v);
		rb->setAngularVelocity(w);

		float hx = .5f, hy = 0.2f, hz = .5f;
		auto geo = PxBoxGeometry(hx, hy, hz);
		auto shape = CreateShape(geo, _mat);
		rb->attachShape(*shape);

		float d = m / (hx * hy * hz);
		PxRigidBodyExt::updateMassAndInertia(*rb, d);

		_system->getScene()->addActor(*rb);
		_system->addRB(rb);

		auto renderItem = new RenderItem(shape, rb, _color);
		_system->addRI(renderItem);
	}
}