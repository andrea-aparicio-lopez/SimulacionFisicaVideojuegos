#include "Obstacle.h"
#include "Player.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "Particle.h"
#include "ExplosionForceGen.h"

#include <iostream>

using namespace physx;

Obstacle::Obstacle(PxVec3 pos, Player* player)
	: _tr(new PxTransform(pos))
	,_player(player) 
{
	// RenderItem
	PxBoxGeometry geo = PxBoxGeometry(1, _halfHeight * 2, 1);
	auto shape = CreateShape(geo);
	_renderItem = new RenderItem(shape, _tr, PxVec4(0.8,0.4,0.2,1));
	RegisterRenderItem(_renderItem);

	// Sistema explosión
	_explSys = new ParticleSystem();
	_explPartGen = new GaussianGen(_explSys, pos, 40.f, PxVec3(0, 1, 0), 1, 20, false);

	Particle* p = new Particle();
	p->setColor({ 0.8,0.5,0,1 });
	p->setLifetime(3.);
	p->setDistance(10.);
	p->removeRenderItem();

	_explPartGen->setPModel(p);
	_explPartGen->setDistAttributes({ 0, 1, 0 }, 10, { 0,0,5 }, 0.);
	_explSys->addParticleGen(_explPartGen);

	_explForceGen = new ExplosionForceGen(pos, 10, 40, 5);
	_explForceGen->setActive(false);


}

Obstacle::~Obstacle() {
	delete _explSys;
	delete _explForceGen;
	DeregisterRenderItem(_renderItem);
}

void Obstacle::update(double dt) {
	if (_alive && _player->getPos().x > _tr->p.x) {
		explode();
	}
	if (_explPartGen->isActive()) _explPartGen->setActive(false);
	_explSys->update(dt);
}

void Obstacle::explode() {
	_alive = false;
	_explPartGen->setActive(true);
	_explForceGen->setActive(true);
	_renderItem->release();
	DeregisterRenderItem(_renderItem);
}