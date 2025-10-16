#include "ScenePSystem.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "Particle.h"

ScenePSystem::ScenePSystem() : Scene() {
}

ScenePSystem::~ScenePSystem() {
	delete _pSystem;
}

void ScenePSystem::start() {
	_pSystem = new ParticleSystem();

	// Generador 1: Amarillas
	auto gen = new GaussianGen(_pSystem, {0,0,15}, 15.f, {0,1,0}, 1.0, 5.0, 1);
	Particle* p = new Particle();
	p->setColor({ 0.8,0.5,0,1 });
	gen->setPModel(p);
	gen->setDistPosVelDir({ 5, 5, 5 }, 10, { 5,0,0 });
	_pSystem->addGen(gen);

	// Generador 2: Blancas
	gen = new GaussianGen(_pSystem, { 0, 100, 0 }, 0, { 0,-1,0 }, 1, 8, 3);
	p = new Particle();
	p->setColor({ 1,1,1,1 });
	gen->setPModel(p);
	gen->setDistPosVelDir({ 50,0,100 }, 5.f, { -1, 0, 0 });
	_pSystem->addGen(gen);

	// Generador 3: Azules
	gen = new GaussianGen(_pSystem, { 40, 20, -10 }, 40.f, { -30,40,0 }, 1, 7, 1);
	p = new Particle();
	p->setColor({ .5,.5,.8,1 });
	gen->setPModel(p);
	gen->setDistPosVelDir({ 1,0,1 }, 3.f, { -0.1, 0, 0 });
	_pSystem->addGen(gen);
}

void ScenePSystem::integrate(double dt) {
	_pSystem->update(dt);
}

void ScenePSystem::processKey(unsigned char key, const physx::PxTransform& camera) {}