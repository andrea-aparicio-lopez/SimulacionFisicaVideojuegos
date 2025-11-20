#pragma once
#include "SpringForceGen.h"
class SpringParticlesForceGen : public SpringForceGen
{
public:
	SpringParticlesForceGen(physx::PxVec3 pos, double k, double l);
	~SpringParticlesForceGen();

	void applyForce(Particle* p) override;

	void setParticles(Particle* p1, Particle* p2);

protected:
	Particle* _p1;
	Particle* _p2;

};

