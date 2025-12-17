#pragma once
#include "RigidGameObjectSystem.h"
class SnowballSystem : public RigidGameObjectSystem
{
public:
	SnowballSystem(physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	~SnowballSystem();

	void update(double dt) override;
	void shoot(physx::PxVec3 pos, physx::PxVec3 dir);

protected:
	const double SHOOTING_COOLDOWN = 1.;

protected:
	double _t = 0;

	bool _isCooldown = false;
	bool _hasShot = false;
};

