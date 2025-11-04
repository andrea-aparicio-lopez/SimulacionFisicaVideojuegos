#include "SceneProyecto.h"
#include "Player.h"
#include "Floor.h"
#include "WeatherParticleSys.h"
#include "Particle.h"
#include "GaussianGen.h"
#include "GravityForceGen.h"

using namespace physx;

SceneProyecto::SceneProyecto() : Scene() {

}

SceneProyecto::~SceneProyecto() {
	Scene::~Scene();
}

void SceneProyecto::start() {
	_player = new Player(PxVec3(0, 0, 0));
	_player->setPos(PxVec3(0, _player->getHalfHeight(), 0));
	_ground = new Floor(PxVec3(0), PxVec4(1, 1, 1,1));

	// WEATHER PARTICLE SYSTEM
	_weather = new WeatherParticleSys(_player);


	// Gravedad
	ForceGenerator* forceGen = new GravityForceGen(PxVec3(0), PxVec3(0,-3,0));
	_weather->addForceGen(forceGen);

	_camera = GetCamera();
}

void SceneProyecto::integrate(double dt) {
	_player->update(dt);
	_weather->update(dt);
}

void SceneProyecto::processKey(unsigned char key, const physx::PxTransform& camera) {
	_player->handleInput(key);
}