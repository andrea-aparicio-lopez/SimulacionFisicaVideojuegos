#include "SceneForceSystem.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"
#include "GaussianGen.h"
#include "GravityForceGen.h"
#include "WindForceGen.h"
#include "TornadoForceGen.h"
#include "ExplosionForceGen.h"

using namespace physx;

SceneForceSystem::SceneForceSystem() : Scene() {
}

SceneForceSystem::~SceneForceSystem() {
	delete _forceSys;
	delete _pSystem;
}

void SceneForceSystem::start() {
	_forceSys = new ForceSystem();
	_pSystem = new ParticleSystem();

	// PARTÍCULAS
	
	// Generador 1: Amarillas
	auto gen = new GaussianGen(_pSystem, { 0,15,0 }, 15.f, { 0,1,0 }, 0.3, 1);

	Particle* p = new Particle();
	p->setColor({ 0.8,0.5,0,1 });
	p->setLifetime(10.);
	p->setDistance(1000.);

	gen->setPModel(p);
	gen->setDistAttributes({ 3, 3, 3 }, 10, { 1,0,0 }, 10.);
	_pSystem->addParticleGen(gen);


	// Generador 2: Azules
	gen = new GaussianGen(_pSystem, { 40, 20, -10 }, 40.f, { -30,40,0 }, .7, 1);

	p = new Particle();
	p->setColor({ .5,.5,.8,1 });
	p->setSize(1.0f);
	p->setLifetime(10.);
	p->setDistance(2000.);
	p->setMass(10.0);

	gen->setPModel(p);
	gen->setDistAttributes({ 1,0,1 }, 3.f, { -0.1, 0, 0 }, 1.0);
	_pSystem->addParticleGen(gen);


	// FUERZAS
	// Gravedad
	ForceGenerator* forceGen = new GravityForceGen(PxVec3(0));
	_forceSys->addForceGen(forceGen);
	_pSystem->addForceGen(forceGen);

	// Viento
	//forceGen = new WindForceGen(PxVec3(0,100,0), PxVec3(80, 50, 100), PxVec3(0,0,-200));
	//_forceSys->addForceGen(forceGen);
	//_pSystem->addForceGen(forceGen);

	// Torbellino
	//forceGen = new TornadoForceGen(PxVec3(0), PxVec3(0,1,0), 100, 6);
	//_forceSys->addForceGen(forceGen);
	//_pSystem->addForceGen(forceGen); 

	// Explosión
	_explosion = new ExplosionForceGen(PxVec3(0), 50, 6000, 2);
	_forceSys->addForceGen(_explosion);
	_pSystem->addForceGen(_explosion); 
}

void SceneForceSystem::integrate(double dt) {
	_forceSys->update(dt);
	_pSystem->update(dt);
}

void SceneForceSystem::processKey(unsigned char key, const physx::PxTransform& camera) {
	if (key == ' ')
		_explosion->setActive(true); 
}