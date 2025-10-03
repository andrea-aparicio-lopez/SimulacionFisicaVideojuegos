#include "Particle.h"

using namespace physx;

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 a, double damping, uint8_t mode)
	: tr(new PxTransform(pos))
	, prevPos(tr->p)
	, vel(vel) 
	, accel(a)
	, damping(damping)
	, integrMode(mode)
{
	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(1.0f);
	auto shape = CreateShape(geo);
	PxVec4 color(1, 1, 1, 1);
	renderItem = new RenderItem(shape, tr, color);
	RegisterRenderItem(renderItem);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}

void Particle::integrate(double t) {
	switch (integrMode)
	{
	case integrateMode::EULER:
		prevPos = tr->p;
		tr->p += t * vel;
		vel += t * accel; 
		vel *= pow(damping, t);
		break;

	case integrateMode::VERLET: {
		auto const currPos = tr->p;
		tr->p = 2 * tr->p - prevPos + pow(t, 2) * accel; 
		prevPos = currPos;
		break;
	}
	case integrateMode::EULER_SEMIIMPLICIT:
	default:
		prevPos = tr->p;
		vel += t * accel; 
		tr->p += t * vel;
		vel *= pow(damping, t);
		break;
	}
}