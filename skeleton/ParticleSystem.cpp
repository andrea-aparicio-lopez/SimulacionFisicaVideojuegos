#include "ParticleSystem.h"

#include "Particle.h"
#include "ParticleGen.h"

ParticleSystem::ParticleSystem() {}

ParticleSystem::~ParticleSystem() {
	for (auto p : _particles)
		delete p;

	for (auto gen : _generators)
		delete gen;
}

void ParticleSystem::update(double dt) {
	for (auto p : _particles)
		p->integrate(dt);

	// eliminar partículas

	// crear particulas 
	for(auto gen : _generators
		gen->generateP();
}