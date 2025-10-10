#pragma once

#include <vector>

#include "Scene.h"
class Projectile;
class Target;
class Floor;

class SceneProjectiles : public Scene
{
public:
	SceneProjectiles();
	~SceneProjectiles() override;

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	std::vector<Projectile*> projectiles;
	Target* target;
	Floor* ground;
};

