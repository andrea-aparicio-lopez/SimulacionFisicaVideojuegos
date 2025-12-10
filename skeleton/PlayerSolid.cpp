#include "PlayerSolid.h"
#include "RenderUtils.hpp"

using namespace physx;

PlayerSolid::PlayerSolid(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos)
	: _gScene(gScene)
{
	auto actorTr = PxTransform(pos);
	_actor = gPhysics->createRigidDynamic(actorTr);

	_playerMat = gPhysics->createMaterial(0.3f, 0.2f, 0.95f);

	// BODY
	auto bodyGeo = PxBoxGeometry(BODY_HX, BODY_HY, BODY_HZ);
	auto bodyShape = CreateShape(bodyGeo, _playerMat);
	//bodyShape->setLocalPose(PxTransform(PxVec3(0)));
	_actor->attachShape(*bodyShape);

	_bodyRI = new RenderItem(bodyShape, _actor, BODY_COLOR);

	// HEAD
	//auto headTr = PxTransform(pos + PxVec3(0, BODY_HY, 0));
	//auto headGeo = PxSphereGeometry(HEAD_R);
	//auto headShape = CreateShape(headGeo, _playerMat);
	//headShape->setLocalPose(headTr);
	//_actor->attachShape(*headShape);

	//_headRI = new RenderItem(headShape, _actor, HEAD_COLOR);

	// TODO:
	// BOARD 
	//auto boardTr

	PxRigidBodyExt::updateMassAndInertia(*_actor, 10.f);


	_gScene->addActor(*_actor);
}

PlayerSolid::~PlayerSolid() {
	_bodyRI->release();
	_gScene->removeActor(*_actor);
}