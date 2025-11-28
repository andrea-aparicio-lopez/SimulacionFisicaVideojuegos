#include "RigidBodyGenerator.h"
#include "RigidBodySystem.h"

RigidBodyGenerator::RigidBodyGenerator(RigidBodySystem* sys, physx::PxVec3 pos, physx::PxVec3 v, physx::PxVec3 w)
	: _system(sys)
	, _pos(pos)
	, _v(v)
	, _w(w)
{

}