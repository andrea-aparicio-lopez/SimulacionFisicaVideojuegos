#include "SceneSprings.h"
#include "ParticleSystem.h"
#include "SpringForceGen.h"
#include "SpringParticlesForceGen.h"
#include "ElasticBandForceGen.h"
#include "GravityForceGen.h"
#include "WindForceGen.h"
#include "Particle.h"
#include "Target.h"

#include <iostream>

using namespace physx;

SceneSprings::SceneSprings() : Scene() {

}

SceneSprings::~SceneSprings() {
	delete _pSystemAnchor;
	delete _anchor;

	for (auto gen : _forceGens)
		delete gen;

	Scene::~Scene();
}

void SceneSprings::start() {

	// ---------- MUELLE 1: Partícula unida a punto fijo -----------------

	_anchor = new Target(PxVec3(-20, 30,10), PxVec3(1.5f));

	_pSystemAnchor = new ParticleSystem();
	ForceGenerator* gravityGen = new GravityForceGen(PxVec3(0));
	_pSystemAnchor->addForceGen(gravityGen);
	_forceGens.push_back(gravityGen);

	_springAnchorForceGen = new SpringForceGen(_anchor->transform()->p, 12, 2);
	_pSystemAnchor->addForceGen(_springAnchorForceGen);
	_forceGens.push_back(_springAnchorForceGen);

	_windForceGen = new WindForceGen(PxVec3(0), PxVec3(100, 25, 100), PxVec3(15, 0, 0));
	_windForceGen->setActive(false);
	_pSystemAnchor->addForceGen(_windForceGen);
	_forceGens.push_back(_windForceGen);

	_pAnchored = new Particle(_anchor->transform()->p - PxVec3(0,20,0), PxVec3(0), PxVec3(0), PxVec4(0.2, 0.8, 0.1, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);
	_pSystemAnchor->addParticle(_pAnchored);


	// ------------- MUELLE 2: Dos partículas unidas ------------------

	_pSystemJoinedParticles = new ParticleSystem();
	//_pSystemJoinedParticles->addForceGen(gravityGen);
	_pSystemJoinedParticles->addForceGen(_windForceGen);

	// Muelle normal (roja-rosa)
	auto springGen = new SpringParticlesForceGen(PxVec3(0), 10., 1.);
	Particle* p1 = new Particle(PxVec3(0, 30, 0), PxVec3(0), PxVec3(0), PxVec4(0.8, 0.2, 0.3, 1.), 1.f, 3.f,DBL_MAX, DBL_MAX);
	Particle* p2 = new Particle(PxVec3(0, 10, 0), PxVec3(0), PxVec3(0), PxVec4(0.9, 0.4, 0.6, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);
	springGen->setParticles(p1, p2);

	_pSystemJoinedParticles->addForceGen(springGen);
	_pSystemJoinedParticles->addParticle(p1);
	_pSystemJoinedParticles->addParticle(p2);

	// Goma elástica (azul-morada)
	springGen = new ElasticBandForceGen(PxVec3(0), 100., 20.);
	p1 = new Particle(PxVec3(10, 30, -10), PxVec3(0), PxVec3(0), PxVec4(0.3, 0.2, 0.8, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);
	p2 = new Particle(PxVec3(10, 5, -10), PxVec3(0), PxVec3(0), PxVec4(0.6, 0.4, 0.9, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);
	springGen->setParticles(p1, p2);

	_pSystemJoinedParticles->addForceGen(springGen);
	_pSystemJoinedParticles->addParticle(p1);
	_pSystemJoinedParticles->addParticle(p2);

	// Slinky
	_pSystemSlinky = new ParticleSystem();
	_pSystemSlinky->addForceGen(gravityGen);

	for (int i = 0; i < 6; ++i) {
		springGen = new SpringParticlesForceGen(PxVec3(0), 10., 2.);
		if (i == 0)
			p1 = new Particle(PxVec3(30, 5*i + 30, -30), PxVec3(0), PxVec3(0), PxVec4(0.1 * 1.5 * i, 0.6, 0.1, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);
		else p1 = p2;
		p2 = new Particle(PxVec3(30, 5 * pow((i + 1),2) + 30, -30), PxVec3(0), PxVec3(0), PxVec4(0.1 * 1.5 * i, 0.6, 0.1, 1.), 1.f, 3.f, DBL_MAX, DBL_MAX);

		springGen->setParticles(p1, p2);

		_pSystemSlinky->addForceGen(springGen);
		_pSystemSlinky->addParticle(p1);
	}
	_pSystemSlinky->addParticle(p2);

}

void SceneSprings::integrate(double dt) {
	_pSystemAnchor->update(dt);
	_pSystemJoinedParticles->update(dt);
	_pSystemSlinky->update(dt);
}

void SceneSprings::processKey(unsigned char key, const physx::PxTransform& camera) {
	switch (toupper(key)) {
	case ' ':
		_windForceGen->setActive(!_windForceGen->isActive());
		_windForceGen->isActive() ? std::cout << "Activando viento\n" : std::cout << "Desactivando viento\n";
		break;
	case 'M':
		// Aumentar k de la partícula unida al punto fijo:
		_springAnchorForceGen->setK(_springAnchorForceGen->getK() + 10.);
		std::cout << "Aumentando k del muelle fijo\n";
		break;
	case 'N':
		// Disminuir k de la partícula unida al punto fijo:
		_springAnchorForceGen->setK(max(_springAnchorForceGen->getK() - 10., 0.));
		std::cout << "Disminuyendo k del muelle fijo\n";
		break;
	default:
		break;
	}
}

