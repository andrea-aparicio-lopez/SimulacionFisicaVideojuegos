#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"

#include <list>

class Player;
class Floor;
class ParticleSystem;
class ForceGenerator;
class Obstacle;
class Projectile;
class Forest;

class SceneProyecto : public Scene
{
public:
	SceneProyecto();
	~SceneProyecto();

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;

protected:
	Player* _player;
	Floor* _ground;
	Forest* _forest;
	
	ParticleSystem* _weatherSys;

	ForceGenerator* _gravityGen;
	ForceGenerator* _windGen;
	ForceGenerator* _tornadoGen;

	std::list<Obstacle*> _obstacles;
	std::list<Projectile*> _projectiles;
	
	Camera* _camera;

};

