#include "SceneProyecto.h"
#include "Player.h"
#include "Floor.h"
#include "WeatherParticleSys.h"
#include "Particle.h"
#include "GaussianGen.h"
#include "GravityForceGen.h"
#include "WindForceGen.h"
#include "TornadoForceGen.h"
#include "Obstacle.h"
#include "Projectile.h"

#include <iostream>

using namespace physx;

SceneProyecto::SceneProyecto() : Scene() {

}

SceneProyecto::~SceneProyecto() {
	delete _player;
	delete _ground;
	delete _weatherSys;
	delete _gravityGen;
	delete _windGen;
	delete _tornadoGen;

	for (auto obs : _obstacles)
		delete obs;

	for (auto p : _projectiles)
		delete p;

	Scene::~Scene();
}

void SceneProyecto::start() {
	_player = new Player(PxVec3(0, 0, 0));
	_player->setPos(PxVec3(0, _player->getHeight(), 0));
	_ground = new Floor(PxVec3(0), PxVec4(1, 1, 1,1));

	// AMBIENTE
	_weatherSys = new WeatherParticleSys(_player);

	// Gravedad
	_gravityGen = new GravityForceGen(PxVec3(0), PxVec3(0,-3,0));
	_weatherSys->addForceGen(_gravityGen);

	// Viento
	_windGen = new WindForceGen(_player->getPos(), PxVec3(100, 30, 10), PxVec3(-15,-5,0));
	_weatherSys->addForceGen(_windGen);

	// Tornado
	_tornadoGen = new TornadoForceGen(_player->getPos() + PxVec3(100,0,0), PxVec3(0, 0, 1), 10, 10);
	_weatherSys->addForceGen(_tornadoGen);


	// OBSTACULO INICIAL
	_obstacles.push_back(new Obstacle(PxVec3(20, 3, 0), _player));

	_camera = GetCamera();
	_camera->setPosition(_player->getPos() + PxVec3(0, 0, 40));
	_camera->setDirection(_player->getPos() - _camera->getEye());
}

void SceneProyecto::integrate(double dt) {
	_player->update(dt);
	for (auto obs : _obstacles)
		obs->update(dt);

	for (auto p : _projectiles)
		p->integrate(dt);

	_weatherSys->update(dt);
	_camera->setPosition(_player->getPos() + PxVec3(0, 0, 50));
}

void SceneProyecto::processKey(unsigned char key, const physx::PxTransform& camera) {
	_player->handleInput(key);

	switch (toupper(key)) {
	case 'G':
		_gravityGen->isActive() ? std::cout << "Desactivando gravedad\n" : std::cout << "Activando gravedad\n";
		_gravityGen->setActive(!_gravityGen->isActive());
		break;
	case 'V':
		_windGen->isActive() ? std::cout << "Desactivando viento\n" : std::cout << "Activando viento\n";
		_windGen->setActive(!_windGen->isActive());
		break;
	case 'T':
		_tornadoGen->isActive() ? std::cout << "Desactivando torbellino\n" : std::cout << "Activando torbellino\n";
		_tornadoGen->setActive(!_tornadoGen->isActive());
		break;
	case 'M':
	{
		// Proyectil disparado desde la cámara
		_projectiles.push_back(new Projectile(camera.p, camera.q.rotate({ 0,0,-1 }), 80.f));
		break;
	}
	default:
		break;
	}
}