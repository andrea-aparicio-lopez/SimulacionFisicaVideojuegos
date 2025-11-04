#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleGen.h"
#include "ForceGenerator.h"

#include <algorithm>
#include <iostream>

ParticleSystem::ParticleSystem() {}

ParticleSystem::~ParticleSystem() {
	for (auto p : _particles)
		delete p;

	for (auto gen : _particleGenerators)
		delete gen;

	// TODO: forceGen compartidos, el sistema no es propietario y no los borra
	for (auto gen : _forceGeneratos)
		delete gen;
}

void ParticleSystem::addParticleGen(ParticleGen* gen) {
	_particleGenerators.push_back(gen);
}

void ParticleSystem::addForceGen(ForceGenerator* gen) {
	_forceGeneratos.push_back(gen);
}

void ParticleSystem::update(double dt) {

	// crear particulas 
	for(auto gen : _particleGenerators)
		gen->generateP();
	
	// aplicar fuerzas y actualizar el generador después
	for (auto f : _forceGeneratos) {
		if (f->isActive()) {
			for (auto p : _particles)
				f->applyForce(p);
			f->update(dt);
		}
	}

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

	// resetear fuerzas
	for (auto p : _particles)
		p->clearForce();

}

void ParticleSystem::addParticle(Particle* p) {
	_particles.push_back(p);
}