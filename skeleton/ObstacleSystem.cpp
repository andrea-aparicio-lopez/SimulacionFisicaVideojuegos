#include "ObstacleSystem.h"
#include "Player.h"
#include "RigidBodyGenerator.h"
#include "ObstacleGen.h"

#include <iostream>

using namespace physx;

ObstacleSystem::ObstacleSystem(PxScene* gScene, PxPhysics* gPhysics, Player* player)
	: RigidGameObjectSystem(gScene, gPhysics)
	, _player(player)
	, _mt()
	, _d_int(0, ObstacleType::OBSTACLE_TYPE_SIZE-1)
	, _d_dist(GEN_DIST_MIN, GEN_DIST_MAX)
	, _d_height(0., GEN_HEIGHT_MAX)
{
	auto obsGen1 = new ObstacleGen(this);
	obsGen1->setActive(false);
	_rbGenerators.push_back(obsGen1);

	auto obsGen2 = new ObstacleGen(this);
	obsGen2->setActive(false);
	_rbGenerators.push_back(obsGen2);

	// TODO: Obstáculos diferentes
}

ObstacleSystem::~ObstacleSystem() {

}

void ObstacleSystem::update(double dt) {
	_t += dt;
	if (_t >= GEN_TIME) {
		_t -= GEN_TIME;

		_canGenerate = true;
		chooseNextObstacleIndex();

		PxVec3 dist = getRdDistance();
		_rbGenerators[_obstacleIndex]->setPos(PxVec3(_player->getPos().x,1.5,0) + dist);
		_rbGenerators[_obstacleIndex]->setActive(true);
	}

	RigidGameObjectSystem::update(dt);

	if (_canGenerate) {
		_rbGenerators[_obstacleIndex]->setActive(false);
		_canGenerate = false;
	}
}

void ObstacleSystem::chooseNextObstacleIndex() {
	_obstacleIndex = _d_int(_mt);
}

PxVec3 ObstacleSystem::getRdDistance() {
	float d = _d_dist(_mt);
	float h = _d_height(_mt);
	return PxVec3(d, h, 0);
}