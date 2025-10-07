#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Projectile
{
// BALA DE ESCOPETA REALISTA:
//	- Masa: ~30g
//	- |Velocidad|: 450 m/s

protected: 
	static constexpr double DAMPING = 0.999;
	static constexpr float V_R = 450.f; // módulo de la velocidad real
	static constexpr float G_R = -9.8f;	// gravedad real
	static constexpr float G_S = -8.f;	// gravedad simulada

public:
	Projectile(physx::PxVec3 pos, physx::PxVec3 dir, float v_sim, physx::PxVec4 color = {.3,.3,.3,1});
	~Projectile();

	void integrate(double t); // Usando integrador de Euler semi-implicito

	void setMass(float m); // setea la masa simulada, recalcula la velocidad sim para conservar la Ec
	void setVel(physx::PxVec3 v); // setea la velocidad sim, recalcula la masa sim para conservar la Ec

	void recalculateMass();
	void recalculateVel();

protected:
	physx::PxTransform* tr;	// posición
	physx::PxVec3 prevPos;	// posición anterior

	float m_r = 0.030f;		// masa real
	float m_s;				// masa simulada

	physx::PxVec3 v_r;		// velocidad real
	physx::PxVec3 v_s;		// velocidad simulada

	physx::PxVec3 a; // aceleración simulada

	float Ec;		// Energía cinética


protected:
	RenderItem* renderItem;

};

