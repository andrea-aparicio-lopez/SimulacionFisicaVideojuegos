#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(
		physx::PxVec3 pos = physx::PxVec3(0), 
		physx::PxVec3 vel = physx::PxVec3(0), 
		physx::PxVec3 a = physx::PxVec3(0), 
		double damping = 0.999,
		uint8_t mode = 1
	);

	~Particle();

	void integrate(double t);

protected:
	physx::PxTransform* tr;	// posición
	physx::PxVec3 prevPos;	// posición anterior
	physx::PxVec3 vel;		// velocidad
	physx::PxVec3 accel;	// aceleración

	double damping;

	RenderItem* renderItem;

	uint8_t integrMode;

public:
	enum integrateMode {
		EULER,
		EULER_SEMIIMPLICIT,
		VERLET
	};
};

