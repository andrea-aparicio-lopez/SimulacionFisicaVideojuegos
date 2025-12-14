#include "PlayerSolid.h"
#include "RenderUtils.hpp"
#include "GameObjectData.h"

#include <iostream>

using namespace physx;

PlayerSolid::PlayerSolid(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos)
	: _gScene(gScene)
{
	auto actorTr = PxTransform(pos);
	_playerMat = gPhysics->createMaterial(0.3f, 0.f, 0.95f);

	// BODY ACTOR
	_actor = gPhysics->createRigidDynamic(actorTr);
	_actor->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z | PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y);
	//_actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	_actor->setAngularDamping(10);
	_actor->setMaxAngularVelocity(4.0f);

	auto bodyGeo = PxBoxGeometry(BODY_HX, BODY_HY, BODY_HZ);
	auto bodyShape = _actor->createShape(bodyGeo, *_playerMat);
	_bodyRI = new RenderItem(bodyShape, _actor, BODY_COLOR);

	GameObjectData* data = new GameObjectData();
	data->type = GameObjectType::PlayerBody;
	data->object = this;
	_actor->userData = data;

	// HEAD ACTOR
	_headActor = gPhysics->createRigidDynamic(actorTr);
	auto headGeo = PxSphereGeometry(HEAD_R);
	auto headShape = _headActor->createShape(headGeo, *_playerMat);
	_headRI = new RenderItem(headShape, _headActor, HEAD_COLOR);

	data = new GameObjectData();
	data->type = GameObjectType::PlayerHead;
	data->object = this;
	_headActor->userData = data;

	// BOARD ACTOR
	_boardActor = gPhysics->createRigidDynamic(actorTr);
	auto boardGeo = PxBoxGeometry(BOARD_HX, BOARD_HY, BOARD_HZ);
	auto boardShape = _boardActor->createShape(boardGeo, *_playerMat);
	_boardRI = new RenderItem(boardShape, _boardActor, BOARD_COLOR);

	data = new GameObjectData();
	data->type = GameObjectType::PlayerBoard;
	data->object = this;
	_boardActor->userData = data;


	PxRigidBodyExt::updateMassAndInertia(*_actor, 1.f);
	PxRigidBodyExt::updateMassAndInertia(*_headActor, 1.f);
	PxRigidBodyExt::updateMassAndInertia(*_boardActor, 1.f);


	// JOINTS
	auto neck = PxFixedJointCreate(*gPhysics, _actor, PxTransform(PxVec3(0,BODY_HY,0)), _headActor, PxTransform(PxVec3(0,-HEAD_R* 1.3,0)));
	auto legs = PxFixedJointCreate(*gPhysics, _actor, PxTransform(PxVec3(0, -BODY_HY, 0)), _boardActor, PxTransform(PxVec3(0, BOARD_HY, 0)));


	_gScene->addActor(*_actor);
	_gScene->addActor(*_headActor);
	_gScene->addActor(*_boardActor);

}

PlayerSolid::~PlayerSolid() {
	_bodyRI->release();

	delete _actor->userData;
	_actor->userData = nullptr;
	_gScene->removeActor(*_actor);

	delete _headActor->userData;
	_headActor->userData = nullptr;
	_gScene->removeActor(*_headActor);

	delete _boardActor->userData;
	_boardActor->userData = nullptr;
	_gScene->removeActor(*_boardActor);
}