#include "SceneProyecto.h"
#include "Player.h"
#include "ForceSystem.h"
#include "WeatherParticleSys.h"
#include "Particle.h"
#include "GaussianGen.h"
#include "GravityForceGen.h"
#include "WindForceGen.h"
#include "TornadoForceGen.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "Environment.h"
#include "GroundSolid.h"
#include "GameObjectData.h"
#include "Snowball.h"
#include "ObstacleSystem.h"
#include "FinishFlag.h"

#include <algorithm>
#include <iostream>

using namespace physx;

SceneProyecto::SceneProyecto(PxScene* gScene, PxPhysics* gPhysics, std::string& display_text1, std::string& display_text2)
	: Scene() 
	, _gScene(gScene)
	, _gPhysics(gPhysics)
	, _display_text1(display_text1)
	, _display_text2(display_text2)
{

}

SceneProyecto::~SceneProyecto() {
	delete _player;
	delete _ground;
	delete _environment;
	delete _finishFlag;
	delete _weatherSys;
	delete _forceSys;
	delete _obstacleSys;

	Scene::~Scene();
}

void SceneProyecto::start() {
	_ground = new GroundSolid(_gScene, _gPhysics, PxVec3(500,0,0), PxVec3(1000, 0.2, 500), PxVec4(1,1,1,1));
	_player = new Player(_gScene, _gPhysics, PxVec3(0, 8, 0));
	_player->setPos(PxVec3(0, _player->getHeight(), 0));

	_forceSys = new ForceSystem();

	// AMBIENTE
	_weatherSys = new WeatherParticleSys(_player);

	// Gravedad
	_gravityGen = new GravityForceGen(PxVec3(0), PxVec3(0,-3,0));
	_forceSys->addForceGen(_gravityGen);
	_weatherSys->addForceGen(_gravityGen);

	// Viento
	_windGen = new WindForceGen(_player->getPos(), PxVec3(150, 50, 10), PxVec3(-15,-5,0));
	_forceSys->addForceGen(_windGen);
	_weatherSys->addForceGen(_windGen);
	_windGen->setActive(false);

	// Tornado
	_tornadoGen = new TornadoForceGen(_player->getPos() + PxVec3(100,0,0), PxVec3(0, 0, 1), 10, 10);
	_forceSys->addForceGen(_tornadoGen);
	_weatherSys->addForceGen(_tornadoGen);
	_tornadoGen->setActive(false);



	// OBSTACULOS
	_obstacleSys = new ObstacleSystem(_gScene, _gPhysics, _player);


	// ÁRBOLES Y MONTAÑAS
	_environment = new Environment(_player);

	// META
	_finishFlag = new FinishFlag(PxVec3(FINISH_LINE, 0, -5));


	_camera = GetCamera();
	_camera->setPosition(_player->getPos() + PxVec3(-10, 0, 40));
	_camera->setDirection(_player->getPos() - _camera->getEye());

	_display_text1 = "Press SPACE to start";
}

void SceneProyecto::integrate(double dt) {
	_forceSys->update(dt);

	_player->update(dt);

	_obstacleSys->update(dt);
	if (_state == Gamestate::RUNNING) {
		_environment->update(dt);
		if (_player->getPos().x >= FINISH_LINE)
			endGame();
	}

	_weatherSys->update(dt);

	_camera->setPosition(_player->getPos() + PxVec3(0, 0, 40));
}

void SceneProyecto::processKey(unsigned char key, const physx::PxTransform& camera) {

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
	case ' ':
		if (_state == START) startGame();
		else if(_state == RUNNING) _player->jump();
		break;
	case 'Q':
		if (_state == RUNNING) _player->shoot();
		break;
	default:
		break;
	}
}

void SceneProyecto::onCollision(PxActor* actor1, PxActor* actor2) 
{
	if (isPlayerActor(actor1) || isPlayerActor(actor2)) {
		bool p = isPlayerActor(actor1);
		PxActor* playerActor = p ? actor1 : actor2;
		PxActor* otherActor = p ? actor2 : actor1;

		auto playerData = reinterpret_cast<GameObjectData*>(playerActor->userData);
		auto otherData = reinterpret_cast<GameObjectData*>(otherActor->userData);
		if (otherData->type == GameObjectType::Ground) { // Colisiones player - ground
			_player->onGroundContact();
		}
		else if (otherData->type == GameObjectType::Obstacle) {	// Colisiones player - obstacle
			auto obstacle = static_cast<Obstacle*>(otherData->object);
			obstacle->explode();
			_score += OBSTACLE_CRASH_POINTS;
			_score = max(_score, 0);
			_display_text2 = "Score: " + std::to_string(_score);
		}
	}
	else { 	// Colisiones snowball - obstacle
		auto data1 = reinterpret_cast<GameObjectData*>(actor1->userData);
		auto data2 = reinterpret_cast<GameObjectData*>(actor2->userData);

		if (data1->type == GameObjectType::Snowball || data2->type == GameObjectType::Snowball) 
		{
			auto snowballData = (data1->type == GameObjectType::Snowball) ? data1 : data2;
			auto otherData = (data1->type == GameObjectType::Snowball) ? data2 : data1;

			auto snowball = static_cast<Snowball*>(snowballData->object);
			snowball->onImpact();

			if (otherData->type == GameObjectType::Obstacle) {
				auto obstacle = static_cast<Obstacle*>(otherData->object);
				obstacle->explode();
				_score += OBSTACLE_DESTROYED_POINTS;
				_display_text2 = "Score: " + std::to_string(_score);
			}
		}
	}
}

bool SceneProyecto::isPlayerActor(PxActor* actor) {
	auto data = reinterpret_cast<GameObjectData*>(actor->userData);

	return data->type == GameObjectType::PlayerBody
		|| data->type == GameObjectType::PlayerHead
		|| data->type == GameObjectType::PlayerBoard;
}

void SceneProyecto::startGame() {
	setState(RUNNING);
	_player->startRun();
	_windGen->setActive(true);
	_tornadoGen->setActive(true);
	_display_text1 = "";
	_display_text2 = "Score: " + std::to_string(_score);
}

void SceneProyecto::endGame() {
	setState(FINISH);
	_player->endRun();
	_windGen->setActive(false);
	_tornadoGen->setActive(false);
	// showScore();
	_display_text1 = "GAME OVER!";
	_display_text2 = "Final Score: " + std::to_string(_score);
}