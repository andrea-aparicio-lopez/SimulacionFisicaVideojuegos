#pragma once

#include <PxPhysicsAPI.h>

class ParticleSystem;
class ParticleGen;
class ForceGenerator;
class Player;
class RenderItem;

class Obstacle
{
public:
	Obstacle(physx::PxVec3 pos, Player* player);
	~Obstacle();

	void update(double dt);

protected:
	void explode();

protected:
	physx::PxTransform* _tr;
	RenderItem* _renderItem;
	float _halfHeight = 1.5f;

	ParticleSystem* _explSys;
	ParticleGen* _explPartGen;
	ForceGenerator* _explForceGen;

	Player* _player; // temporal, para saber cuándo explotar hasta que haya colisiones

	bool _alive = true;
};

