#include "ParticleGen.h"
#include "ParticleSystem.h"
#include "Particle.h"

using namespace physx;

ParticleGen::ParticleGen(ParticleSystem* sys, physx::PxVec3 pos, float vel, physx::PxVec3 dir, 
						double probGen, int n) 
	: _pSystem(sys)
	, _pos(pos)
	, _vel(vel)
	, _dir(dir)

	, _probGen(probGen)
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

void ParticleGen::setDistAttributes(PxVec3 distPos, float distVel, PxVec3 distDir, double distLifetime) {
	_distPos = distPos;
	_distVel = distVel;
	_distDir = distDir;
	_distLifetime = distLifetime;
}

void ParticleGen::setPModel(Particle* p) {
	delete _pModel;
	_pModel = p;
}