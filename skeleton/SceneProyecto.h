#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"

#include <list>

class Player;
class GroundSolid;
class ParticleSystem;
class ForceSystem;
class ForceGenerator;
//class Obstacle;
class ObstacleSystem;
class Forest;

class SceneProyecto : public Scene
{
public:
	SceneProyecto(physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	~SceneProyecto();

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;

protected:
	bool isPlayerActor(physx::PxActor* actor);	// Gestión de colisiones

protected:
	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;

protected:
	Player* _player;
	GroundSolid* _ground;
	Forest* _forest;
	
	ParticleSystem* _weatherSys;
	ForceSystem* _forceSys;

	ForceGenerator* _gravityGen;
	ForceGenerator* _windGen;
	ForceGenerator* _tornadoGen;

	ObstacleSystem* _obstacleSys;
	//std::list<Obstacle*> _obstacles;
	//std::list<Projectile*> _projectiles;

	
	Camera* _camera;


protected:
	enum Gamestate {
		START,
		RUNNING,
		WIN,
		LOSE
	};

	Gamestate _state = START;

public:
	void setState(Gamestate state) { _state = state; }
};

