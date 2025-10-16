#include "GaussianGen.h"
#include "Particle.h"
#include "ParticleSystem.h"

#include <PxPhysicsAPI.h>
#include <list>
#include <exception>

using namespace physx;

GaussianGen::GaussianGen(ParticleSystem* sys, PxVec3 pos, float vel, PxVec3 dir, 
						double probGen, double lifetime, int n)
	: ParticleGen(sys, pos, vel, dir, probGen, lifetime, n)
{

}

GaussianGen::~GaussianGen() {
	delete _pModel;
}

void GaussianGen::generateP() {
	if (_pModel == nullptr)
		throw new std::exception("No se ha registrado una partícula modelo");

	std::list<Particle*> newParticles;

	for (int i = 0; i < _nParticles; ++i) {
		// probGen
		PxVec3 pos = _pos + _d(_mt) * _distPos;
		float vel = _vel + _d(_mt) * _distVel;
		PxVec3 dir = _dir + _d(_mt) * _distDir;
		dir.normalize();

		Particle* p = new Particle(_pModel);
		p->setPos(pos);
		p->setVel(dir * vel);
		p->setAccel(_accel);
		p->setLifetime(_lifetime);
		
		newParticles.push_back(p);
	}
	for (auto p : newParticles) {
		_pSystem->addParticle(p);
	}
}