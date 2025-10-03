#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Arrow
{
// FLECHA REALISTA:
//	- Masa: ~20g
//	- |Velocidad|: 80 m/s

protected: 
	static constexpr double DAMPING = 0.999;
	static constexpr float V_R = 80.f; // módulo de la velocidad real
	static constexpr float G_R = 9.8f;	// gravedad real
	static constexpr float G_S = 5.f;	// gravedad simulada

public:
	Arrow(physx::PxVec3 pos, physx::PxVec3 dir, float v_sim);
	~Arrow();

	void integrate(double t); // Usando integrador de Euler semi-implicito

protected:
	physx::PxTransform* tr;	// posición
	physx::PxVec3 prevPos;	// posición anterior

	float m_r = 20.f;		// masa real
	float m_s;				// masa simulada

	physx::PxVec3 v_r;		// velocidad real
	physx::PxVec3 v_s;		// velocidad simulada

	physx::PxVec3 a; // aceleracion, es 0

	float Ec;		// Energía cinética


protected:
	RenderItem* renderItem;

};

