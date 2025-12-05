#pragma once
#include "ForceGenerator.h"

class DragForceGen : public ForceGenerator
{
public:
	DragForceGen(physx::PxVec3 pos, double u);

	void applyForce(Particle* p) override;
	void applyForce(physx::PxRigidBody* rb) override;
	void update(double dt) override;

protected:
	double _u;
	double _g = 9.8;
	double _ug;
};

