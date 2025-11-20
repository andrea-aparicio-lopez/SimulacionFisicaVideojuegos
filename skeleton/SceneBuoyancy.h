#pragma once
#include "Scene.h"

class ParticleSystem;
class ForceGenerator;
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
    ForceGenerator* _buoyantForceGen;
    ForceGenerator* _gravityForceGen;

    Particle* _p;
};

