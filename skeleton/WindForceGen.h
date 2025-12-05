#pragma once
#include "ForceGenerator.h"

class WindForceGen : public ForceGenerator
{
public:
	WindForceGen(physx::PxVec3 pos, physx::PxVec3 range, physx::PxVec3 v, double k1 = 1.0, double k2 = 0.);
	~WindForceGen();

	virtual void applyForce(Particle* p) override;
	virtual void applyForce(physx::PxRigidBody* rb) override;
	virtual void update(double dt) override;

protected:
	physx::PxVec3 _range; // Area de efecto (pos-range, pos+range)
	physx::PxVec3 _v;
	double _k1;
	double _k2;

protected:
	virtual bool withinRange(physx::PxVec3 const& pos) const;
};

