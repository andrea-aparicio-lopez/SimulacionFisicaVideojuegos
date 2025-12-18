#include "WeatherParticleSys.h"
#include "Player.h"
#include "GaussianGen.h"
#include "WindForceGen.h"
#include "particle.h"
#include <iostream>

using namespace physx;

WeatherParticleSys::WeatherParticleSys(Player* player)
	: ParticleSystem()
	, _player(player)
{
	auto snowGen = new GaussianGen(this, _player->getPos() +_offset, 0, { 0,-1,0 }, .5, 10);
	auto p = new Particle();
	p->setColor({ 1,1,1,1 });
	p->setSize(0.1f);
	p->setMass(0.5f);
	p->setLifetime(20.);
	p->setDistance(200.);
	p->removeRenderItem();
	snowGen->setPModel(p);
	snowGen->setDistAttributes({ 80,0,0 }, 0.f, { -1, 0, 0 }, .0);
	addParticleGen(snowGen);


}

WeatherParticleSys::~WeatherParticleSys() {
	ParticleSystem::~ParticleSystem();
}

void WeatherParticleSys::update(double dt) {
	for (auto gen : _particleGenerators) 
		gen->setPos(Vector3(_player->getPos().x,0,0) + _offset);

	for (auto gen : _forceGenerators)
		gen->setPos(_player->getPos());
	
	ParticleSystem::update(dt);

}