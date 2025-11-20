#pragma once
#include "Scene.h"

#include <vector> 

class ParticleSystem;
class ForceGenerator;
class SpringForceGen;

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
	std::vector<ForceGenerator*> _forceGens;
	ForceGenerator* _windForceGen;
	SpringForceGen* _springAnchorForceGen;

	ParticleSystem* _pSystemAnchor;
	Particle* _pAnchored;
	Target* _anchor;

	ParticleSystem* _pSystemJoinedParticles;
};

