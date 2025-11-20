#include "SceneSprings.h"
#include "ParticleSystem.h"
#include "SpringForceGen.h"
#include "GravityForceGen.h"
#include "Particle.h"
#include "Target.h"


using namespace physx;

SceneSprings::SceneSprings() : Scene() {

}

SceneSprings::~SceneSprings() {
	delete _pSystem;
	//delete _pAnchored;
	delete _anchor;

	Scene::~Scene();
}

void SceneSprings::start() {
	_pSystem = new ParticleSystem();
	ForceGenerator* forceGen = new GravityForceGen(PxVec3(0));
	_pSystem->addForceGen(forceGen);

	forceGen = new SpringForceGen(PxVec3(0, 30, 0), 1.5, 2);
	_pSystem->addForceGen(forceGen);

	_pAnchored = new Particle(PxVec3(0), PxVec3(0), PxVec3(0), PxVec4(0.2, 0.9, 0.1, 1.), 1.f);
	_pAnchored->setLifetime(DBL_MAX);
	_pAnchored->setDistance(DBL_MAX);
	_pSystem->addParticle(_pAnchored);

	_anchor = new Target(PxVec3(0, 30,0), PxVec3(2.f));
}

void SceneSprings::integrate(double dt) {
	_pSystem->update(dt);
}

void SceneSprings::processKey(unsigned char key, const physx::PxTransform& camera) {
	switch (toupper(key)) {
	case ' ':
		_pAnchored->addForce(PxVec3(-20, 0, 0));
		break;
	default:
		break;
	}
}

