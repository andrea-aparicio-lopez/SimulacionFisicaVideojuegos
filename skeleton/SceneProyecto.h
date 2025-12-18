#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"

#include <list>

class Player;
class GroundSolid;
class ParticleSystem;
class ForceSystem;
class ForceGenerator;
class ObstacleSystem;
class Forest;
class FinishFlag;

class SceneProyecto : public Scene
{
public:
	SceneProyecto(physx::PxScene* gScene, physx::PxPhysics* gPhysics, std::string& display_text1, std::string& display_text2);
	~SceneProyecto();

	void start() override;

	void integrate(double dt) override;
	void processKey(unsigned char key, const physx::PxTransform& camera) override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;

protected:
	bool isPlayerActor(physx::PxActor* actor);	// Gestión de colisiones

	void startGame();
	void endGame();

protected:
	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;

	std::string& _display_text1;
	std::string& _display_text2;

protected:
	Player* _player;
	GroundSolid* _ground;
	Forest* _forest;
	FinishFlag* _finishFlag;
	
	ParticleSystem* _weatherSys;
	ForceSystem* _forceSys;

	ForceGenerator* _gravityGen;
	ForceGenerator* _windGen;
	ForceGenerator* _tornadoGen;

	ObstacleSystem* _obstacleSys;
	
	Camera* _camera;

	// Puntuación
	int _score = 0;
	const int OBSTACLE_DESTROYED_POINTS = 5;
	const int OBSTACLE_CRASH_POINTS = -3;

	const float FINISH_LINE = 1000.f;

protected:
	enum Gamestate {
		START,
		RUNNING,
		FINISH
	};

	Gamestate _state = START;

public:
	void setState(Gamestate state) { _state = state; }
};

