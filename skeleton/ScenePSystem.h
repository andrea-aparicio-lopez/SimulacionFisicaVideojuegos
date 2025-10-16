#pragma once
#include "Scene.h"

class ParticleSystem;

class ScenePSystem : public Scene
{
public:
	ScenePSystem();
	~ScenePSystem() override;

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	ParticleSystem* _pSystem;
};

