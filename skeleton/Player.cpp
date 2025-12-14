#include "Player.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "TrailParticleGen.h"
#include "Projectile.h"
#include "GaussianRBGen.h"
#include "RigidBodySystem.h"
#include "ImpulseForceGen.h"
#include "ForceSystem.h"

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

}

Player::~Player() {
	delete _trailSys;

	for (auto p : _projectiles)
		delete p;
}

void Player::update(double dt) {
	if (_running) {
		_playerSolid.getActor()->setLinearVelocity(PxVec3(10, _playerSolid.getActor()->getLinearVelocity().y, 0));
		_trailGen->setPos(_playerSolid.getBottomLeftPos());
	}
	_playerRBSystem->update(dt);
	_trailSys->update(dt);

	for (auto p : _projectiles)
		p->integrate(dt);
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
	// TODO: cambiar proyectiles a sistema sólidos
	_projectiles.push_back(new Projectile(getPos(), PxVec3(1,0.15,0), 60.f, PxVec4(1,0,0.8,1)));
}