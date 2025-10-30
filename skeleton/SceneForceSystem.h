#pragma once
#include "Scene.h"

class ParticleSystem;

class SceneForceSystem : public Scene
{
public:
	SceneForceSystem();
	~SceneForceSystem() override;

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	ParticleSystem* _pSystem;
};

