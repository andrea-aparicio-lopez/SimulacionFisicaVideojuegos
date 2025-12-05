#pragma once
#include <list>
#include <PxPhysicsAPI.h>

class RigidBodyGenerator;
class ForceGenerator;

class RigidBodySystem
{
public: 
	RigidBodySystem();
	~RigidBodySystem();

protected:
	std::list<physx::PxRigidBody*> _rbs;
	std::list<RigidBodyGenerator*> _rbGenerators;

	std::list<ForceGenerator*> _forceGenerators; // TODO: forceSystem

public:
	void addRB(physx::PxRigidBody* rb);
	void addRBGen(RigidBodyGenerator* gen);
	void addForceGen(ForceGenerator* gen);

	virtual void update(double dt);
};

