#pragma once

#include <list>

class Particle;
class ParticleGen;
class GaussianGen;
class UniformGen;
class ForceGenerator;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _particleGenerators;

	std::list<ForceGenerator*> _forceGeneratos;

	void addParticle(Particle* p);

public:
	void addParticleGen(ParticleGen* gen);
	void addForceGen(ForceGenerator* gen);

	void update(double dt);

	friend ParticleGen;
	friend GaussianGen;
	friend UniformGen;
};

