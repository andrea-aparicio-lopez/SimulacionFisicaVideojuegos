#include "SceneBuoyancy.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Target.h"
#include "BuoyantForceGen.h"
#include "GravityForceGen.h"
#include "DragForceGen.h"
#include "ForceSystem.h"

#include <iostream>

using namespace physx;

SceneBuoyancy::SceneBuoyancy() {

}

SceneBuoyancy::~SceneBuoyancy() {
	delete _water;
	delete _pSys;
	delete _forceSys;

	Scene::~Scene();
}

void SceneBuoyancy::start() {
	_water = new Target(PxVec3(0, 50, 0), PxVec3(30, 0.2, 30), PxVec4(0.1, 0.1, 1, 1));

	_forceSys = new ForceSystem();
	_pSys = new ParticleSystem();

	auto gravityForceGen = new GravityForceGen(PxVec3(0));
	_forceSys->addForceGen(gravityForceGen);
	_pSys->addForceGen(gravityForceGen);

	auto dragForceGen = new DragForceGen(PxVec3(0), 0.5);
	_forceSys->addForceGen(dragForceGen);
	_pSys->addForceGen(dragForceGen);

	auto buoyantForceGen = new BuoyantForceGen(_water->transform()->p, 1000.f);
	_forceSys->addForceGen(buoyantForceGen);
	_pSys->addForceGen(buoyantForceGen);

	// Partícula 1 sobre el agua inicialmente
	Particle* p = new Particle(_water->transform()->p + PxVec3(-10, 10, 10), PxVec3(0), PxVec3(0), PxVec4(0.8, 0.8, 0.8, 1.), 1.f, 1500.f, DBL_MAX, DBL_MAX);
	PxBoxGeometry geo = PxBoxGeometry(PxVec3(1,3,1));
	PxShape* shape = CreateShape(geo);
	auto rI = new RenderItem(shape, p->getTr(), p->getColor());
	p->setRenderItem(rI);

	_pSys->addParticle(p);

	// Partícula 2 medio hundida inicialmente. Masa modificable por teclado
	p = new Particle(_water->transform()->p + PxVec3(0, 0, 0), PxVec3(0), PxVec3(0), PxVec4(0.5, 0.8, 0.9, 1.), 1.f, 3000.f, DBL_MAX, DBL_MAX);
	shape = CreateShape(geo);
	rI = new RenderItem(shape, p->getTr(), p->getColor());
	p->setRenderItem(rI);

	_pSys->addParticle(p);
	_p = p;

	// Partícula 3 completamente sumergida inicialmente
	p = new Particle(_water->transform()->p + PxVec3(10, -10, -10), PxVec3(0), PxVec3(0), PxVec4(0.8, 0.8, 0.8, 1.), 1.f, 6000.f, DBL_MAX, DBL_MAX);
	shape = CreateShape(geo);
	rI = new RenderItem(shape, p->getTr(), p->getColor());
	p->setRenderItem(rI);

	_pSys->addParticle(p);

}

void SceneBuoyancy::integrate(double dt) {
	_forceSys->update(dt);
	_pSys->update(dt);
}

void SceneBuoyancy::processKey(unsigned char key, const physx::PxTransform& camera) {
	switch (toupper(key))
	{
	case 'M':
		_p->setMass(_p->getMass() + 100.f);
		std::cout << "Aumentando masa\n";
		break;
	case 'N':
		_p->setMass(max(1.0, _p->getMass() - 100.f));
		std::cout << "Reduciendo masa\n";
		break;
	default:
		break;
	}
}