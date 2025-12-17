#include "ObstacleGen.h"
#include "RigidGameObjectSystem.h"
#include "Obstacle.h"

using namespace physx;

ObstacleGen::ObstacleGen(RigidBodySystem* sys)
	: RigidBodyGenerator(sys, PxVec3(0), 1.f, PxVec3(0), PxVec3(0))
{
	setDiffAttributes(PxVec3(0), 0.f, PxVec3(0), PxVec3(0));
}

ObstacleGen::~ObstacleGen() {

}


void ObstacleGen::generateRigidBody() {

	auto system = static_cast<RigidGameObjectSystem*>(_system);

	auto obstacle = new Obstacle(_system->getScene(), _system->getPhysics(), _pos);
	system->addGameObject(obstacle);
}
