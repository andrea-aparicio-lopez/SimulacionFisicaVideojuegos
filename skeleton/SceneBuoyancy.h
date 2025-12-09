#pragma once
#include "Scene.h"

class ParticleSystem;
class ForceSystem;
class Target;
class Particle;

class SceneBuoyancy : public Scene
{
public:
    SceneBuoyancy();
    ~SceneBuoyancy();

    void start() override;

    void integrate(double dt) override;
    void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
    Target* _water;
    ParticleSystem* _pSys;
    ForceSystem* _forceSys;

    Particle* _p;
};

