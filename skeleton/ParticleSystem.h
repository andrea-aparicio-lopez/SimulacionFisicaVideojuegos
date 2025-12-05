#pragma once

#include <list>
#include <memory>

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

	std::list<ForceGenerator*> _forceGenerators; // La escena es responsable de borrar los generadores de fuerzas, no el sistema


public:
	void addParticle(Particle* p);
	void addParticleGen(ParticleGen* gen);
	void addForceGen(ForceGenerator* gen);

	virtual void update(double dt);

	//friend ParticleGen;
	//friend GaussianGen;
	//friend UniformGen;
};

