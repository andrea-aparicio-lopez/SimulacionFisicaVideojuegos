#include "ParticleGen.h"
#include "ParticleSystem.h"
#include "Particle.h"

using namespace physx;

ParticleGen::ParticleGen(ParticleSystem* sys, physx::PxVec3 pos, float vel, physx::PxVec3 dir, 
						double probGen, double lifetime, int n) 
	: _pSystem(sys)
	, _pos(pos)
	, _vel(vel)
	, _dir(dir)
	, _probGen(probGen)
	, _lifetime(lifetime)
	, _nParticles(n)
	, _pModel(nullptr)

	, _distPos(0)
	, _distVel(0)
	, _distDir(0)
{
	_dir.normalize();
}

ParticleGen::~ParticleGen() {
	delete _pModel;
}

void ParticleGen::setDistPosVelDir(PxVec3 distPos, float distVel, PxVec3 distDir) {
	_distPos = distPos;
	_distVel = distVel;
	_distDir = distDir;
}

void ParticleGen::setPModel(Particle* p) {
	delete _pModel;
	_pModel = p;
}