#include "ScenePSystem.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "Particle.h"

ScenePSystem::ScenePSystem() : Scene() {
}

ScenePSystem::~ScenePSystem() {
	delete _pSystem;
}

void ScenePSystem::start() {
	_pSystem = new ParticleSystem();

	// Generador 1: Amarillas
	auto gen = new GaussianGen(_pSystem, {0,0,15}, 15.f, {0,1,0}, 0.3, 1);

	Particle* p = new Particle();
	p->setColor({ 0.8,0.5,0,1 });
	p->setLifetime(3.);
	p->setDistance(100.);

	gen->setPModel(p);
	gen->setDistAttributes({ 5, 5, 5 }, 10, { 5,0,0 }, 10.);
	_pSystem->addParticleGen(gen);

	// Generador 2: Blancas
	gen = new GaussianGen(_pSystem, { 0, 100, 0 }, 0, { 0,-1,0 }, .1, 3);

	p = new Particle();
	p->setColor({ 1,1,1,1 });
	p->setSize(0.3f);
	p->setLifetime(7.);
	p->setDistance(150.);

	gen->setPModel(p);
	gen->setDistAttributes({ 50,0,100 }, 5.f, { -1, 0, 0 }, 5.0);
	_pSystem->addParticleGen(gen);

	// Generador 3: Azules
	gen = new GaussianGen(_pSystem, { 40, 20, -10 }, 40.f, { -30,40,0 }, .7, 1);

	p = new Particle();
	p->setColor({ .5,.5,.8,1 });
	p->setSize(1.0f);
	p->setLifetime(7.);
	p->setDistance(200.);

	gen->setPModel(p);
	gen->setDistAttributes({ 1,0,1 }, 3.f, { -0.1, 0, 0 }, 1.0);
	_pSystem->addParticleGen(gen);


	// Generador 4 UNIFORME: Verdes
	auto uGen = new UniformGen(_pSystem, { 40, 0, 10 }, 30.0f, { 1,0,0 }, .5, 1);

	p = new Particle();
	p->setColor({ .3,.55,.3,1 });
	p->setSize(1.0f);
	p->setLifetime(7.);
	p->setDistance(100.);

	uGen->setPModel(p);
	uGen->setDistAttributes({ 5,0,5 }, 5.f, { -0.5, 0, 0 }, 1.0);
	_pSystem->addParticleGen(uGen);

}

void ScenePSystem::integrate(double dt) {
	_pSystem->update(dt);
}

void ScenePSystem::processKey(unsigned char key, const physx::PxTransform& camera) {}