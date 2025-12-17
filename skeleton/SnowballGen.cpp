#include "SnowballGen.h"
#include "Snowball.h"
#include "RigidGameObjectSystem.h"
#include <iostream>

using namespace physx;

SnowballGen::SnowballGen(RigidBodySystem* sys)
	: RigidBodyGenerator(sys, PxVec3(0), SNOWBALL_MASS, PxVec3(1,0,0), SNOWBALL_W)
{
	setDiffAttributes(PxVec3(0), 0.f, PxVec3(0), PxVec3(0));
}

SnowballGen::~SnowballGen() {

}

void SnowballGen::generateRigidBody() {

		auto system = static_cast<RigidGameObjectSystem*>(_system);

		auto snowball = new Snowball(system->getScene(), system->getPhysics(), _pos, SNOWBALL_V_MAGNITUDE * _v);
		system->addGameObject(snowball);
}

