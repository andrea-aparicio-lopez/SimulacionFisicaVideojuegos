#pragma once

#include <random>
#include <PxPhysicsAPI.h>

class ParticleSystem;
class Particle;

class ParticleGen
{
protected:
	ParticleGen(ParticleSystem* sys, physx::PxVec3 pos, float vel, physx::PxVec3 dir, 
				double probGen, int n = 1);

public:
	virtual ~ParticleGen();
	virtual void generateP() = 0;

protected:
	physx::PxVec3 _pos;
	float _vel;	// magnitude
	physx::PxVec3 _dir;

	physx::PxVec3 _distPos;
	float _distVel;
	physx::PxVec3 _distDir;
	double _distLifetime;

	double _probGen;
	int _nParticles;

	std::mt19937 _mt;
	// std::uniform_real_distribution<double> _u{ 0,1 };

	ParticleSystem* _pSystem;
	Particle* _pModel;

public:
	inline physx::PxVec3 getPos() const { return _pos; }
	inline float getVel() const { return _vel; }
	inline physx::PxVec3 getDir() const { return _dir; }
	inline float getProbGen() const { return _probGen; }

	inline void setPos(physx::PxVec3 pos) { _pos = pos; }
	inline void setVel(float vel) { _vel = vel; }
	inline void setDir(physx::PxVec3 dir) { dir.normalize(); _dir = dir; }
	inline void setProbGen(float prob) { _probGen = prob; }

	void setDistAttributes(physx::PxVec3 distPos, float distVel, physx::PxVec3 distDir, double distLifetime);
	
	void setPModel(Particle* p);

};

