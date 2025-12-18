#include "SnowballSystem.h"
#include "SnowballGen.h"

using namespace physx;

SnowballSystem::SnowballSystem(PxScene* gScene, PxPhysics* gPhysics)
	: RigidGameObjectSystem(gScene, gPhysics)
{

}

SnowballSystem::~SnowballSystem() {

}

void SnowballSystem::update(double dt) {
	if (_isCooldown) {
		_t += dt;
		if (_t >= SHOOTING_COOLDOWN) {

			_t = 0.;
			_isCooldown = false;
		}
	}

	// Actualiza
	RigidGameObjectSystem::update(dt);

	// Desactiva generador de snowballs si estaba activo
	if (_hasShot) { 
		for (auto gen : _rbGenerators) 
			gen->setActive(false);
		_hasShot = false;
	}
}

void SnowballSystem::shoot(PxVec3 pos, PxVec3 dir) {
	if (!_isCooldown) {
		_hasShot = true;
		_isCooldown = true;

		for (auto gen : _rbGenerators) {
			gen->setPos(pos);
			gen->setV(dir);
			gen->setActive(true);
		}
	}
}