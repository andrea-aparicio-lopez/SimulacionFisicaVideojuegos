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
		float size = 0.5f,
		double mass = 1.0f,
		double lifetime = 1000,
		double dist = 100,
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
	float _size;	// radio

	double _lifetime;
	double _distance;
	bool _alive;

	double _damping;
	uint8_t _integrMode;

	RenderItem* _renderItem;

	double _massInv;	// Inverso de la masa
	physx::PxVec3 _force;

public:
	physx::PxVec3 getPos() const;
	void setPos(physx::PxVec3 pos);

	physx::PxVec3 getVel() const;
	void setVel(physx::PxVec3 vel);

	physx::PxVec3 getAccel() const;
	void setAccel(physx::PxVec3 a);

	physx::PxVec4 getColor() const;
	void setColor(physx::PxVec4 color);

	void setSize(float size);

	double getLifetime() const;
	void setLifetime(double lifetime);
	void setDistance(double dist);
	bool isAlive() const;

	enum integrateMode {
		EULER,
		EULER_SEMIIMPLICIT,
		VERLET
	};

	double getMass() const;
	void setMass(double m);

	void addForce(physx::PxVec3 force);
	void clearForce();
};

