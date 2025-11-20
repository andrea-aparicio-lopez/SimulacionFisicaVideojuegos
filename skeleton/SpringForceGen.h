#pragma once
#include "ForceGenerator.h"

class SpringForceGen : public ForceGenerator
{
public:
	SpringForceGen(physx::PxVec3 pos, double k, double l);
	~SpringForceGen();

	void applyForce(Particle* p) override;
	void update(double dt) override;

	double getK() const;
	void setK(double k);

protected:
	double _k;
	double _l; // longitud en reposo
};

