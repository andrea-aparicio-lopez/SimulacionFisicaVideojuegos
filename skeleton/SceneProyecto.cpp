#include "SceneProyecto.h"
#include "Player.h"
#include "Floor.h"
#include "ParticleSystem.h"

using namespace physx;

SceneProyecto::SceneProyecto() : Scene() {

}

SceneProyecto::~SceneProyecto() {
	Scene::~Scene();
}

void SceneProyecto::start() {
	_player = new Player(PxVec3(0, 0, 0));
	_ground = new Floor(PxVec3(0));
	_weather = new ParticleSystem();
}

void SceneProyecto::integrate(double dt) {
	_player->integrate(dt);
	_weather->update(dt);
}

void SceneProyecto::processKey(unsigned char key, const physx::PxTransform& camera) {

}