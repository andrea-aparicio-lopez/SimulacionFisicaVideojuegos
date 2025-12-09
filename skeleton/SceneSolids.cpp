#include "SceneSolids.h"
#include "ForceSystem.h"
#include "RigidBodySystem.h"
#include "GaussianRBGen.h"
#include "WindForceGen.h"
#include "TornadoForceGen.h"
#include "RenderUtils.hpp"

using namespace physx;

SceneSolids::SceneSolids(physx::PxScene* gScene, physx::PxPhysics* gPhysics) 
	: _gScene(gScene)
	, _gPhysics(gPhysics)
{

}

SceneSolids::~SceneSolids() {
	delete _forceSys;
	delete _rbSys;

	//_gScene->removeActor(*_ground);
	//_groundRI->release();
}

void SceneSolids::start() {
	_forceSys = new ForceSystem();
	_rbSys = new RigidBodySystem(_gScene, _gPhysics);

	// ------- GENERADOR DE SÓLIDOS ----------
	// Generador 1: Sólidos magenta
	RigidBodyGenerator* rbGen = new GaussianRBGen(_rbSys, PxVec3(0, 10, -20), 10.f, PxVec3(10, 5, 0), PxVec3(1,0,0));
	rbGen->setDiffAttributes(PxVec3(0, 0.5f, 0), 1.0f, PxVec3(0, 5, 0), PxVec3(1, 0, 0));
	rbGen->setColor(PxVec4(0.7, 0.0f, 0.5f, .5f));
	auto material = _gPhysics->createMaterial(0.3f, 0.2f, 0.95f);
	rbGen->setMaterial(material);
	_rbSys->addRBGen(rbGen);

	// Generador 2: Sólidos azules
	rbGen = new GaussianRBGen(_rbSys, PxVec3(0, 10, 20), 10.f, PxVec3(10, 5, 0), PxVec3(1, 0, 0));
	rbGen->setDiffAttributes(PxVec3(0, 0.5f, 0), 1.0f, PxVec3(0, 5, 0), PxVec3(1, 0, 0));
	rbGen->setColor(PxVec4(0.1f, 0.0f, 0.8f, 1.f));
	material = _gPhysics->createMaterial(0.8f, 0.8f, 0.2f);
	rbGen->setMaterial(material);
	_rbSys->addRBGen(rbGen);


	// -------- FUERZAS ---------
	// VIENTO
	//auto forceGen = new WindForceGen(PxVec3(0), PxVec3(50, 50, 50), PxVec3(0, 0, -30));
	//_forceSys->addForceGen(forceGen);
	//_rbSys->addForceGen(forceGen);

	// TORBELLINO
	_tornadoGen = new TornadoForceGen(PxVec3(0), PxVec3(0, 1, 0), 60, 20.);
	_tornadoGen->setActive(false);
	_forceSys->addForceGen(_tornadoGen);
	_rbSys->addForceGen(_tornadoGen);

	// SUELO
	auto tr = PxTransform(PxVec3(0));
	auto geo = PxBoxGeometry(50., 0.1, 50.);
	auto shape = CreateShape(geo);
	_ground = _gPhysics->createRigidStatic(tr);
	_ground->attachShape(*shape);

	_groundRI = new RenderItem(shape, _ground, _groundColor);
	_gScene->addActor(*_ground);

}

void SceneSolids::integrate(double dt) {
	_forceSys->update(dt);
	_rbSys->update(dt);
}

void SceneSolids::processKey(unsigned char key, const physx::PxTransform& camera) {
	switch (toupper(key)) {
	case 'N':
		_tornadoGen->setActive(!_tornadoGen->isActive());
		break;
	default:
		break;
	}
}