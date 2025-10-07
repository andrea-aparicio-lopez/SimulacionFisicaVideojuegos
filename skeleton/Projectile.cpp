#include "Projectile.h"

using namespace physx;

Projectile::Projectile(PxVec3 pos, PxVec3 dir, float v_sim, PxVec4 color)
	: tr(new PxTransform(pos))
	, a(PxVec3(0, G_S, 0))
{
	// Calcular velocidades real y simulada
	dir.normalize();
	v_r = dir * V_R;
	v_s = dir * v_sim;

	// Calcular Energía cinética
	Ec = 1.f / 2 * m_r * pow(v_r.magnitude(), 2);

	// Calcular masa simulada
	recalculateMass();


	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(.5);
	auto shape = CreateShape(geo);
	renderItem = new RenderItem(shape, tr, color);
	RegisterRenderItem(renderItem);
}

Projectile::~Projectile() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}

void Projectile::integrate(double t) {
	prevPos = tr->p;
	v_s += t * a;
	tr->p += t * v_s;
	v_s *= pow(DAMPING, t);
}

void Projectile::setMass(float m) {
	m_s = m;
	recalculateVel();
}

void Projectile::setVel(PxVec3 v) {
	v_s = v;
	recalculateMass();
}

void Projectile::recalculateMass() {
	m_s = 2 * Ec / pow(v_s.magnitude(), 2);
}

void Projectile::recalculateVel() {
	auto mag = sqrt(2 * Ec / m_s);
	v_s.normalize();
	v_s *= mag;
}