#include "Arrow.h"

using namespace physx;

Arrow::Arrow(PxVec3 pos, PxVec3 dir, float v_sim)
	: tr(new PxTransform(pos))
	, a(PxVec3(0))
{
	// Calcular velocidades real y simulada
	dir.normalize();
	v_r = dir * V_R;
	v_s = dir * v_sim;

	// Calcular Energía cinética
	Ec = 1.f / 2 * m_r * pow(v_r.magnitude(), 2);

	// Calcular masa simulada
	m_s = 2 * Ec / pow(v_s.magnitude(), 2);


	// Inicializar RenderItem
	PxBoxGeometry geo = PxBoxGeometry(1, 1, 5);
	auto shape = CreateShape(geo);
	PxVec4 color(.8, .8, .2, 1);
	renderItem = new RenderItem(shape, tr, color);
	RegisterRenderItem(renderItem);
}

Arrow::~Arrow() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}

void Arrow::integrate(double t) {
	prevPos = tr->p;
	v_s += t * a;
	tr->p += t * v_s;
	v_s *= pow(DAMPING, t);
}