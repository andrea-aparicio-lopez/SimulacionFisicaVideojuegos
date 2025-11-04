#pragma once

#include <PxPhysicsAPI.h>

class Particle;

class ForceGenerator
{
protected:
	ForceGenerator(physx::PxVec3 pos, bool active = true);

public:
	~ForceGenerator();
	virtual void applyForce(Particle* p) = 0;
	virtual void update(double dt) = 0;

	bool isActive() const;
	virtual void setActive(bool v);

	void setPos(physx::PxVec3 pos);

protected:
	physx::PxVec3 _pos;

	bool _active;
};

