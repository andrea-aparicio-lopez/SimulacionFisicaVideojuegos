#pragma once

#include <PxPhysicsAPI.h>
#include <random>

class RigidBodySystem;

class RigidBodyGenerator
{
public:
	RigidBodyGenerator(RigidBodySystem* sys, physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w);
	~RigidBodyGenerator();

public:
	inline physx::PxVec3 getPos() const { return _pos; }
	inline void setPos(physx::PxVec3 pos) { _pos = pos; }

	inline physx::PxVec3 getV() const { return _v; }
	inline void setV(physx::PxVec3 v) { _v = v; }

	inline physx::PxVec3 getW() const { return _w; }
	inline void setW(physx::PxVec3 w) { _w = w; }

	//inline physx::PxVec3 getInertiaTensor() const { return _inertiaTensor; }
	//inline void setInertiaTensor(physx::PxVec3 iT) { _inertiaTensor = iT; }

	inline bool isActive() const { return _active; }
	inline void setActive(bool v) {_active = v; }

	void setDiffAttributes(physx::PxVec3 diffPos, float diffM, physx::PxVec3 diffV, physx::PxVec3 diffW);

public:
	virtual void generateRigidBody();

protected:
	RigidBodySystem* _system;

	physx::PxVec3 _pos;
	float _m;
	physx::PxVec3 _v;
	physx::PxVec3 _w;
	//physx::PxVec3 _inertiaTensor;

	// Atributos para añadir aleatoriedad
	physx::PxVec3 _diffPos;
	float _diffM;
	physx::PxVec3 _diffV;
	physx::PxVec3 _diffW;

protected:
	std::mt19937 _mt;


protected:
	bool _active;
};

