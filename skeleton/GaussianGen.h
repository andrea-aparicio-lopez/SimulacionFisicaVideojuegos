#pragma once
#include "ParticleGen.h"

namespace physx {
	class PxVec3;
}


class GaussianGen : public ParticleGen
{
public:
	GaussianGen(ParticleSystem* sys, physx::PxVec3 pos, float vel, physx::PxVec3 dir, 
				double probGen, double lifetime, int n);
	~GaussianGen();

	void generateP() override;

protected:
	std::normal_distribution<double> _d{ 0,1 };

	physx::PxVec3 _accel = {0, -10., 0};
};

