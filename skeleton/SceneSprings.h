#pragma once
#include "Scene.h"

class ParticleSystem;
class Particle;
class Target;

class SceneSprings : public Scene
{
public:
	SceneSprings();
	~SceneSprings();

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	ParticleSystem* _pSystem;
	Particle* _pAnchored;
	Target* _anchor;
};

