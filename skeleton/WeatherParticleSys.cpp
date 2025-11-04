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
	auto snowGen = new GaussianGen(this, _player->getPos() +_offset, 5, { 0,-1,0 }, .5, 3);
	auto p = new Particle();
	p->setColor({ 1,0,1,1 });
	p->setSize(0.3f);
	p->setLifetime(10.);
	p->setDistance(80.);
	snowGen->setPModel(p);
	snowGen->setDistAttributes({ 20,0,0 }, 0.f, { -1, 0, 0 }, 3.0);
	addParticleGen(snowGen);

	//auto windGen = new WindForceGen();
}

WeatherParticleSys::~WeatherParticleSys() {
	ParticleSystem::~ParticleSystem();
}

void WeatherParticleSys::update(double dt) {
	for (auto gen : _particleGenerators) 
		gen->setPos(_player->getPos() + _offset);
	
	ParticleSystem::update(dt);

}