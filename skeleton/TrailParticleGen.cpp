#include "TrailParticleGen.h"
#include "Particle.h"
#include "ParticleSystem.h"

using namespace physx;

TrailParticleGen::TrailParticleGen(ParticleSystem* sys, PxVec3 pos)
	: GaussianGen(sys, pos, 10.f, PxVec3(-1, 0, 0), 0.3, 1)
{
	Particle* p = new Particle();
	p->setColor({ 0,1,1,1 });
	p->setLifetime(2.);
	p->setDistance(3.);
	p->setSize(0.15);
	p->removeRenderItem();

	setPModel(p);
	setDistAttributes({ 0, 0.2, 0 }, 1, { 1,0,0 }, 0.5);
}

TrailParticleGen::~TrailParticleGen() {
	GaussianGen::~GaussianGen();
}