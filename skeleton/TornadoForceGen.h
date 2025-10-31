#pragma once
#include "WindForceGen.h"
class TornadoForceGen : public WindForceGen
{
public:
	TornadoForceGen(physx::PxVec3 pos, physx::PxVec3 axis, double r, double k = 5.0, double k1 = 1.0, double k2 = 0.);
	~TornadoForceGen();

	virtual void applyForce(Particle* p) override;

protected:
	physx::PxVec3 _axis; // Eje central del torbellino
	double _r;	// radio

	double _k;	// cte fuerza torbellino

protected:
	bool withinRange(physx::PxVec3 const& pos) const override;
	physx::PxVec3 getVel(physx::PxVec3 const& pos) const;
};

