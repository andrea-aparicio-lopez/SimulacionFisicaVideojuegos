#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"

class Player;
class Floor;
class ParticleSystem;

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
	ParticleSystem* _weather;
	Camera* _camera;

};

