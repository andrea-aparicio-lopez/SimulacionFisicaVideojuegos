#pragma once

#include <list>

class Particle;
class ParticleGen;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;

public:
	void update(double dt);
};

