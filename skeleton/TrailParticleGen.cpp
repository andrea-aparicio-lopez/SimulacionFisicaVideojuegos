#include "TrailParticleGen.h"
#include "Particle.h"
#include "ParticleSystem.h"

using namespace physx;

TrailParticleGen::TrailParticleGen(ParticleSystem* sys, PxVec3 pos)
	: GaussianGen(sys, pos, 10.f, PxVec3(-1, 0, 0), 0.2, 1)
{
	Particle* p = new Particle();
	p->setColor({ 0,1,1,1 });
	p->setLifetime(1.);
	p->setDistance(2.);
	p->setSize(0.15);

	setPModel(p);
	setDistAttributes({ 0, 0, 0.5 }, 1, { 1,0,0 }, 0.5);
}

TrailParticleGen::~TrailParticleGen() {
	GaussianGen::~GaussianGen();
}