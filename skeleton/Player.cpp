#include "Player.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "TrailParticleGen.h"
#include "Projectile.h"

#include <iostream>

using namespace physx;

Player::Player(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos)
	//_player(new Particle(pos, PxVec3(0, 0, 0), PxVec3(0), PxVec4(0.3, 0.55, 0.3, 1), 1.0, 50., 0., 0.))
	: _playerActor(PlayerSolid(gScene, gPhysics, pos))
{
	// ! BORRAR
	// Inicializar RenderItem de _player
	//PxBoxGeometry geo = PxBoxGeometry(1,_halfHeight*2,1);
	//PxShape* shape = CreateShape(geo);
	//auto item = new RenderItem(shape, _player->getTr(), _player->getColor());
	//_player->setRenderItem(item);
	

	// RASTRO
	_trailSys = new ParticleSystem();
	_trailGen = new TrailParticleGen(_trailSys, pos);
	_trailSys->addParticleGen(_trailGen);

}

Player::~Player() {
	//delete _player;
	delete _trailSys;

	for (auto p : _projectiles)
		delete p;
}

void Player::update(double dt) {
	//_player->integrate(dt);
	//if (_player->getVel() != PxVec3(0)) {
	//	_trailGen->setPos(_player->getPos() - PxVec3(_player->getSize(), _halfHeight, 0));
	//	_trailSys->update(dt);
	//}

	for (auto p : _projectiles)
		p->integrate(dt);
}

void Player::handleInput(unsigned char key) {
	switch (toupper(key)) {
	case ' ':
		//if (_player->getVel() == PxVec3(0))
		//	_player->setVel(PxVec3(10, 0, 0));
		//else shoot();
		break;
	default:
		break;
	}
}

PxVec3 Player::getPos() {
	//return _player->getPos();
	return _playerActor.getActor()->getGlobalPose().p;
}

void Player::setPos(PxVec3 pos) {
	//_player->setPos(pos);
	_playerActor.getActor()->setGlobalPose(PxTransform(pos));
}

float Player::getHeight() const {
	return _halfHeight * 2;
}
float Player::getHalfHeight() const {
	return _halfHeight;
}

void Player::shoot() {
	// TODO: cambiar proyectiles a sistema sólidos
	_projectiles.push_back(new Projectile(getPos(), PxVec3(1,0.15,0), 60.f, PxVec4(1,0,0.8,1)));
}