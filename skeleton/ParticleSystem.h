#pragma once

#include <list>

class Particle;
class ParticleGen;
class GaussianGen;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;

	void addParticle(Particle* p);

public:
	void addGen(ParticleGen* gen);

	void update(double dt);

	friend ParticleGen;
	friend GaussianGen;
};

