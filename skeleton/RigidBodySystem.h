#pragma once
#include <list>
#include <PxPhysicsAPI.h>

class RigidBodyGenerator;
class ForceGenerator;
class RenderItem;

class RigidBodySystem
{
public: 
	RigidBodySystem(physx::PxScene* gScene);
	~RigidBodySystem();

public:
	void addRB(physx::PxRigidBody* rb);
	void addRI(RenderItem* ri);
	void addRBGen(RigidBodyGenerator* gen);
	void addForceGen(ForceGenerator* gen);

	physx::PxScene* getScene() const;

	virtual void update(double dt);

protected:
	double _genTime = 1000.; // ms
	double t = 0.;

protected:
	std::list<physx::PxRigidBody*> _rbs;
	std::list<RenderItem*> _renderItems;
	std::list<RigidBodyGenerator*> _rbGenerators;

	std::list<ForceGenerator*> _forceGenerators;

	physx::PxScene* _gScene;
};

