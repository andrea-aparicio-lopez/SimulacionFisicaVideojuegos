#pragma once
#include "GaussianGen.h"

class ParticleSystem;

class TrailParticleGen : public GaussianGen
{
public:
    TrailParticleGen(ParticleSystem* sys, physx::PxVec3 pos);
    ~TrailParticleGen();
};

