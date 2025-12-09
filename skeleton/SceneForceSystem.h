#pragma once
#include "Scene.h"

class ForceSystem;
class ParticleSystem;
class ExplosionForceGen;

class SceneForceSystem : public Scene
{
public:
	SceneForceSystem();
	~SceneForceSystem() override;

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	ForceSystem* _forceSys;
	ParticleSystem* _pSystem;
	ExplosionForceGen* _explosion;
};

