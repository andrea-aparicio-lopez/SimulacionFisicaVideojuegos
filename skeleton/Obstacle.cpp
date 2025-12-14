#include "Obstacle.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "Particle.h"
#include "ExplosionForceGen.h"
#include "GameObjectData.h"

#include <iostream>

using namespace physx;

Obstacle::Obstacle(PxScene* gScene, PxPhysics* gPhysics,  PxVec3 pos)
	: _gScene(gScene)
{
	// ------- SOLIDO RÍGIDO -------
	auto tr = PxTransform(pos);

	_actor = gPhysics->createRigidStatic(tr);
	PxBoxGeometry geo = PxBoxGeometry(1, _halfHeight * 2, 1);
	PxShape* shape = CreateShape(geo);
	_actor->attachShape(*shape);

	_renderItem = new RenderItem(shape, _actor, PxVec4(0.8,0.4,0.2,1));

	GameObjectData* data = new GameObjectData();
	data->type = GameObjectType::Obstacle;
	data->object = this;
	_actor->userData = data;

	gScene->addActor(*_actor); // TODO: add actor to aggregate from RBSystem


	// -------- EXPLOSIÓN --------
	_explSys = new ParticleSystem();
	_explPartGen = new GaussianGen(_explSys, pos, 40.f, PxVec3(0, 1, 0), 5, 50, false);

	Particle* p = new Particle();
	p->setColor({ 0.8,0.5,0,1 });
	p->setSize(0.3f);
	p->setMass(5.f);
	p->setLifetime(3.);
	p->setDistance(20.);
	p->removeRenderItem();

	_explPartGen->setPModel(p);
	_explPartGen->setDistAttributes({ 0, 1, 0 }, 10, {3,0,0 }, 0.);
	_explSys->addParticleGen(_explPartGen);

	_explForceGen = new ExplosionForceGen(pos, 10, 40, 5);
	_explForceGen->setActive(false);

}

Obstacle::~Obstacle() {
	delete _explSys;
	delete _explForceGen;
	if(_renderItem != nullptr) _renderItem->release();

	delete _actor->userData;
	_actor->userData = nullptr;


}

void Obstacle::update(double dt) {
	if (!_alive && _actor != nullptr) {
		_actor->release();
		_actor = nullptr;

		_renderItem->release();
		_renderItem = nullptr;
	}

	_explSys->update(dt);
	if (_explPartGen->isActive()) _explPartGen->setActive(false);

}

void Obstacle::explode() {
	if (_alive) {
		_alive = false;
		_explPartGen->setActive(true);
		_explForceGen->setActive(true);
		
		//_actor->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
	}
}