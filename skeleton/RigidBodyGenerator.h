#pragma once

#include <PxPhysicsAPI.h>
#include <random>

class RigidBodySystem;

class RigidBodyGenerator
{
public:
	RigidBodyGenerator(RigidBodySystem* sys, physx::PxVec3 pos, float m, physx::PxVec3 v, physx::PxVec3 w, physx::PxMaterial* mat = nullptr);
	~RigidBodyGenerator();

public:
	inline physx::PxVec3 getPos() const { return _pos; }
	inline void setPos(physx::PxVec3 pos) { _pos = pos; }

	inline physx::PxVec3 getV() const { return _v; }
	inline void setV(physx::PxVec3 v) { _v = v; }

	inline physx::PxVec3 getW() const { return _w; }
	inline void setW(physx::PxVec3 w) { _w = w; }

	inline physx::PxMaterial* getMaterial() const { return _mat; }
	inline void setMaterial(physx::PxMaterial* mat) { _mat = mat; }

	inline physx::PxVec4 getColor() const { return _color; }
	inline void setColor(physx::PxVec4 color) { _color = color; }

	inline double getGenTime() const { return _genTime; }
	inline void setGenTime(double genTime) { _genTime = genTime; }

	inline bool isActive() const { return _active; }
	inline void setActive(bool v) {_active = v; }

	void setDiffAttributes(physx::PxVec3 diffPos, float diffM, physx::PxVec3 diffV, physx::PxVec3 diffW);

public:
	virtual void generateRigidBody() = 0;
	void update(double dt);

protected:
	RigidBodySystem* _system;

	physx::PxVec3 _pos;
	float _m;
	physx::PxVec3 _v;
	physx::PxVec3 _w;
	
	physx::PxMaterial* _mat;
	physx::PxVec4 _color = { 1.f, 0.f, 0.f, 1.0f };

	// Atributos para añadir aleatoriedad
	physx::PxVec3 _diffPos;
	float _diffM;
	physx::PxVec3 _diffV;
	physx::PxVec3 _diffW;

protected:
	std::mt19937 _mt;

	double _genTime = .2; // s
	double t = 0.;

protected:
	bool _active;
	bool _canGenerate = true;
};

