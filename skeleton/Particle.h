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
		physx::PxVec4 color = physx::PxVec4(1),
		double lifetime = 1000,
		double damping = 0.999,
		uint8_t mode = 1
	);

	Particle(Particle* const& other);

	~Particle();

	void integrate(double dt);

protected:
	physx::PxTransform* _tr;	// posición
	physx::PxVec3 _prevPos;	// posición anterior
	physx::PxVec3 _vel;		// velocidad
	physx::PxVec3 _accel;	// aceleración
	physx::PxVec4 _color;

	double _lifetime;
	bool _alive;

	double _damping;

	RenderItem* _renderItem;

	uint8_t _integrMode;

public:
	physx::PxVec3 getPos() const;
	void setPos(physx::PxVec3 pos);

	physx::PxVec3 getVel() const;
	void setVel(physx::PxVec3 vel);

	physx::PxVec3 getAccel() const;
	void setAccel(physx::PxVec3 a);

	physx::PxVec4 getColor() const;
	void setColor(physx::PxVec4 color);

	void setLifetime(double lifetime);
	bool isAlive() const;

	enum integrateMode {
		EULER,
		EULER_SEMIIMPLICIT,
		VERLET
	};
};

