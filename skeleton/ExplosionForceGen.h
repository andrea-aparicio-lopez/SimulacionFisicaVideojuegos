#pragma once
#include "ForceGenerator.h"

class ExplosionForceGen : public ForceGenerator
{
public:
	ExplosionForceGen(physx::PxVec3 pos, double r, double k);
	~ExplosionForceGen();

	void applyForce(Particle* p) override;

protected:
	// TODO: onda expansiva, radio inicial = 0
	double _r;	// radio de explosi�n
	double _k; // fuerza de la exlosi�n
};

