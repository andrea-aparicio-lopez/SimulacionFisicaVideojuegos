#include "Player.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "TrailParticleGen.h"
#include "Projectile.h"
#include "GaussianRBGen.h"
#include "RigidBodySystem.h"
#include "ImpulseForceGen.h"
#include "ForceSystem.h"
#include "SnowballSystem.h"
#include "SnowballGen.h"
#include "GravityForceGen.h"
#include "DragForceGen.h"
#include "ElasticBandForceGen.h"
#include "WindForceGen.h"

#include <iostream>

using namespace physx;

Player::Player(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos)
	: _playerSolid(PlayerSolid(gScene, gPhysics, pos))
{
	_playerRBSystem = new RigidBodySystem(gScene, gPhysics);
	_playerRBSystem->addRB(_playerSolid.getActor());

	_jumpImpulseForceGen = new ImpulseForceGen(pos, JUMP_IMPULSE);
	_jumpImpulseForceGen->setActive(false);
	_forceSys.addForceGen(_jumpImpulseForceGen);
	_playerRBSystem->addForceGen(_jumpImpulseForceGen);

	// RASTRO
	_trailSys = new ParticleSystem();
	_trailGen = new TrailParticleGen(_trailSys, _playerSolid.getBottomLeftPos());
	_trailGen->setActive(false);
	_trailSys->addParticleGen(_trailGen);

	// BOLAS DE NIEVE
	_snowballSystem = new SnowballSystem(gScene, gPhysics);
	auto snowballGen = new SnowballGen(_snowballSystem);
	snowballGen->setActive(false);
	_snowballSystem->addRBGen(snowballGen);

	// BUFANDA
	auto gravityGen = new GravityForceGen(PxVec3(0, -9.8, 0));
	_forceSys.addForceGen(gravityGen);

	_scarfWind = new WindForceGen(_playerSolid.getScarfPos(), PxVec3(50, 10, 10), PxVec3(-2, 0, 0)); // viento más suave que el del clima
	_forceSys.addForceGen(_scarfWind);

	auto dragGen = new DragForceGen(PxVec3(0), 0.75);
	_forceSys.addForceGen(dragGen);

	_scarf = new ParticleSystem();
	_scarf->addForceGen(gravityGen);
	_scarf->addForceGen(dragGen);
	_scarf->addForceGen(_scarfWind);

	Particle *p1, *p2;
	for (int i = 0; i < 15; ++i) {
		auto springGen = new ElasticBandForceGen(PxVec3(0), 150., .1);
		_forceSys.addForceGen(springGen);
		if (i == 0) {
			p1 = new Particle(_playerSolid.getScarfPos(), PxVec3(0), PxVec3(0), PxVec4(0.05 *  i , 0.3, 0.6, 1.), .2f, .1f, DBL_MAX, DBL_MAX);
			_scarfAnchor = p1;
		}
		else p1 = p2;
		p2 = new Particle(_playerSolid.getScarfPos(), PxVec3(0), PxVec3(0), PxVec4(0.05 * i, 0.3, 0.6, 1.), .2f, .1f, DBL_MAX, DBL_MAX);

		springGen->setParticles(p1, p2);

		_scarf->addForceGen(springGen);
		_scarf->addParticle(p1);
	}
	_scarf->addParticle(p2);
}

Player::~Player() {
	delete _trailSys;
	delete _snowballSystem;
}

void Player::update(double dt) {
	if (_running) {
		_playerSolid.getActor()->setLinearVelocity(PxVec3(10, _playerSolid.getActor()->getLinearVelocity().y, 0));
		_trailGen->setPos(_playerSolid.getBottomLeftPos());
		_scarfWind->setPos(_playerSolid.getScarfPos());
	}
	_playerRBSystem->update(dt);
	_snowballSystem->update(dt);

	_trailSys->update(dt);
	
	_scarfAnchor->setPos(_playerSolid.getScarfPos());
	_scarf->update(dt);
}

PxVec3 Player::getPos() {
	return _playerSolid.getActor()->getGlobalPose().p;
}

void Player::setPos(PxVec3 pos) {
	_playerSolid.getActor()->setGlobalPose(PxTransform(pos));
}

PxVec3 Player::getBottomPos() const {
	return _playerSolid.getBottomPos();
}

float Player::getHeight() const {
	return _halfHeight * 2;
}
float Player::getHalfHeight() const {
	return _halfHeight;
}

bool Player::getCanJump() const {
	return _canJump;
}

void Player::setCanJump(bool v) {
	_canJump = v;
}

bool Player::getRunning() const {
	return _running;
}

void Player::setRunning(bool v) {
	_running = v;
}

void Player::startRun() {
	_running = true;
	_trailGen->setActive(true);
}

void Player::onGroundContact() {
	if (_running) {
		_canJump = true;
		_trailGen->setActive(true);
	}
}

void Player::jump() {
	if (_canJump) {
		_jumpImpulseForceGen->setActive(true);
		_trailGen->setActive(false);
		_canJump = false;
	}
	_playerSolid.getActor()->addTorque(PxVec3(0, 0, 5000));
}

void Player::shoot() {
	_snowballSystem->shoot(_playerSolid.getShootingPos(), _playerSolid.getShootingDir());
}