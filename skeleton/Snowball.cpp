#include "Snowball.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "GaussianGen.h"
#include "ExplosionForceGen.h"
#include "RenderUtils.hpp"
#include "GameObjectData.h"

#include <iostream>
using namespace physx;

Snowball::Snowball(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos, physx::PxVec3 v)
	: RigidGameObject()
{
	// ------- SOLIDO RÍGIDO -------
	auto tr = PxTransform(pos);

	_actor = gPhysics->createRigidDynamic(tr);
	PxSphereGeometry geo = PxSphereGeometry(R);
	PxShape* shape = CreateShape(geo);
	_actor->attachShape(*shape);


	_renderItem = new RenderItem(shape, _actor, COLOR);

	GameObjectData* data = new GameObjectData();
	data->type = GameObjectType::Snowball;
	data->object = this;
	_actor->userData = data;

	PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);
	PxRigidBodyExt::updateMassAndInertia(*actor, 1.f);
	actor->setLinearVelocity(v);

	gScene->addActor(*_actor); // TODO: add actor to aggregate from RBSystem



	// -------- EXPLOSIÓN --------
	_explSys = new ParticleSystem();
	_explPartGen = new GaussianGen(_explSys, pos, 40.f, PxVec3(0, 1, 0), 1, 20, false);

	Particle* p = new Particle();
	p->setColor(COLOR);
	p->setSize(0.15f);
	p->setMass(.2f);
	p->setLifetime(2.);
	p->setDistance(5.);
	p->removeRenderItem();

	_explPartGen->setPModel(p);
	_explPartGen->setDistAttributes({ 0, 0.2, 0 }, 10, { 3,0,0 }, 0.);
	_explSys->addParticleGen(_explPartGen);

	_explForceGen = new ExplosionForceGen(pos, 5, 40, 5);
	_explForceGen->setActive(false);

}

Snowball::~Snowball() {

}

void Snowball::onImpact() {
	if (_alive) {
		_alive = false;
		_explPartGen->setPos(_actor->getGlobalPose().p);
		_explPartGen->setActive(true);
		_explForceGen->setPos(_actor->getGlobalPose().p);
		_explForceGen->setActive(true);
	}
}