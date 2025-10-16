#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleGen.h"

#include <algorithm>
#include <iostream>

ParticleSystem::ParticleSystem() {}

ParticleSystem::~ParticleSystem() {
	for (auto p : _particles)
		delete p;

	for (auto gen : _generators)
		delete gen;
}

void ParticleSystem::addGen(ParticleGen* gen) {
	_generators.push_back(gen);
}

void ParticleSystem::update(double dt) {

	// crear particulas 
	for(auto gen : _generators)
		gen->generateP();
	
	// actualizar partículas
	for (auto p : _particles)
		p->integrate(dt);

	// eliminar partículas
	_particles.erase(std::remove_if(_particles.begin(), _particles.end(),
		[](Particle* p) {
			if (!p->isAlive()) {
				delete p;
				return true;
			}
			return false;
		}), _particles.end());
}

void ParticleSystem::addParticle(Particle* p) {
	_particles.push_back(p);
}