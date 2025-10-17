#pragma once
#include "ParticleGen.h"

namespace physx {
	class PxVec3;
}

class UniformGen : public ParticleGen
{
public:
	UniformGen(ParticleSystem* sys,
		physx::PxVec3 pos, float vel, physx::PxVec3 dir,
		double probGen, int n = 1);
	~UniformGen();

	void generateP() override;

protected:
	std::uniform_real_distribution<double> _u{ 0,1 };

	physx::PxVec3 _accel = { 0, -10., 0 };
};

