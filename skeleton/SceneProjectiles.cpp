#include "SceneProjectiles.h"

#include <PxPhysicsAPI.h>

#include "Projectile.h"
#include "Target.h"
#include "Floor.h"

using namespace physx;

SceneProjectiles::SceneProjectiles() : Scene() {}

SceneProjectiles::~SceneProjectiles() {
	for (auto p : projectiles)
		delete p;

	delete target;
	delete ground;
}

void SceneProjectiles::start() {
	ground = new Floor(PxVec3(0));
	target = new Target(PxVec3(-100, 5, -100), PxVec3(10, 10, 3));
}

void SceneProjectiles::integrate(double dt) {
	for (auto p : projectiles)
		p->integrate(dt);
}

void SceneProjectiles::processKey(unsigned char key, const PxTransform& camera) {
	switch (toupper(key))
	{
	case ' ':
	{
		// Bala por defecto
		projectiles.push_back(new Projectile(camera.p, camera.q.rotate({0,0,-1}), 80.f));
		break;
	}
	case 'M':
		// Bala más pesada y lenta
		projectiles.push_back(new Projectile(camera.p, camera.q.rotate({ 0,0,-1 }), 80.f, {.6,.6,.2,1}));
		projectiles[projectiles.size() - 1]->setMass(3.f);
		break;
	case 'N':
		// Bala más rápida
		projectiles.push_back(new Projectile(camera.p, camera.q.rotate({ 0,0,-1 }), 250.f, { .6,0,.2,1 }));
		break;
	default:
		break;
	}
}

