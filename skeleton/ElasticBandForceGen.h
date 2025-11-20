#pragma once
#include "SpringParticlesForceGen.h"
class ElasticBandForceGen : public SpringParticlesForceGen
{
public:
	ElasticBandForceGen(physx::PxVec3 pos, double k, double l);
	~ElasticBandForceGen();

	void applyForce(Particle* p) override;
};

