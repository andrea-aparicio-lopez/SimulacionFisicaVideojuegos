#pragma once
#include "Scene.h"
#include <PxPhysicsAPI.h>

class ForceSystem;
class ForceGenerator;
class RigidBodySystem;
class RenderItem;

class SceneSolids : public Scene
{
public:
	SceneSolids(physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	~SceneSolids();

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;

protected:
	ForceSystem* _forceSys;
	ForceGenerator* _tornadoGen;
	RigidBodySystem* _rbSys;

	physx::PxRigidStatic* _ground;
	RenderItem* _groundRI;
	const physx::PxVec4 _groundColor = { 0.1, 0.3, 0.1, 1. };
};

