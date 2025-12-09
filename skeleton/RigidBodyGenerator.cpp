#include "RigidBodyGenerator.h"
#include "RigidBodySystem.h"

using namespace physx;

RigidBodyGenerator::RigidBodyGenerator(RigidBodySystem* sys, physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w, PxMaterial* mat)
	: _system(sys)
	, _pos(pos)
	, _m(m)
	, _v(v)
	, _w(w)
	, _mat(mat)
{

}

RigidBodyGenerator::~RigidBodyGenerator() {

}

void RigidBodyGenerator::setDiffAttributes(PxVec3 diffPos, float diffM, PxVec3 diffV, PxVec3 diffW) {
	_diffPos = diffPos;
	_diffM = diffM;
	_diffV = diffV;
	_diffW = diffW;
}

void RigidBodyGenerator::update(double dt) 
{
	t += dt;
	if (t >= _genTime) {
		t -= _genTime;
		_canGenerate = true;
	}
}