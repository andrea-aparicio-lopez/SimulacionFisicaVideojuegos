#pragma once
#include "RigidGameObjectSystem.h"

#include <random>

class Player;

class ObstacleSystem : public RigidGameObjectSystem
{
public:
	ObstacleSystem(physx::PxScene* gScene, physx::PxPhysics* gPhysics, Player* player);
	~ObstacleSystem();

	void update(double dt) override;

protected:
	void chooseNextObstacleIndex();
	physx::PxVec3 getRdDistance();

protected:
	const double GEN_TIME = 2.5;
	const float GEN_DIST_MIN = 70.f;
	const float GEN_DIST_MAX = 100.f;
	const float GEN_HEIGHT_MAX = 20.f;

protected:
	Player* _player; // para conocer la posición

	double _t = 0;
	bool _canGenerate = false;
	int _obstacleIndex;

	std::mt19937 _mt;
	std::uniform_int_distribution<> _d_int;
	std::uniform_real_distribution<float> _d_dist;
	std::uniform_real_distribution<float> _d_height;

	enum ObstacleType {
		BLOCK,
		//ROCK,
		//HOUSE,
		//BONFIRE,
		OBSTACLE_TYPE_SIZE
	};


};

