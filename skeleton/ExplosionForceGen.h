#pragma once
#include "ForceGenerator.h"

class ExplosionForceGen : public ForceGenerator
{
public:
	ExplosionForceGen(physx::PxVec3 pos, double r, double k, double t);
	~ExplosionForceGen();

	void applyForce(Particle* p) override;
	virtual void update(double dt) override;
	virtual void setActive(bool v) override;

protected:
	const double V_EXP = 340.; // velocidad expansión sonido en aire
	double _r;		// radio con onda expansiva
	//double _rMax;	// radio máximo de explosión
	double _k; // fuerza de la exlosión

	double _duration;	// duración total de la explosión
	double _t = 0.;		// tiempo que lleva activa
	double _exp = 1.0;	// e^(-t/T)


};

