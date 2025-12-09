#include "GaussianRBGen.h"
#include "RigidBodySystem.h"

using namespace physx;

GaussianRBGen::GaussianRBGen(RigidBodySystem* sys,
	physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w)
	: RigidBodyGenerator(sys, pos, m, v, w)
{

}

GaussianRBGen::~GaussianRBGen() {
	RigidBodyGenerator::~RigidBodyGenerator();
}

void GaussianRBGen::generateRigidBody() {

	// Un poco de aleatoriedad
	PxVec3 pos = _pos + _d(_mt) * _diffPos;
	float m = _m + _d(_mt) * _diffM;
	PxVec3 v = _v + _d(_mt) * _diffV;
	PxVec3 w = _w + _d(_mt) * _diffW;

	//PxTransform tr = PxTransform()
	//_system->getScene()->addActor();
}