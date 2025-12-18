#pragma once
#include <PxPhysicsAPI.h>

class RenderItem;

class PlayerSolid
{
public:
	PlayerSolid(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~PlayerSolid();

	inline physx::PxRigidDynamic* getActor() { return _actor; }
	inline physx::PxRigidDynamic* getHeadActor() { return _headActor; }
	inline physx::PxRigidDynamic* getBoardActor() { return _boardActor; }
	inline physx::PxVec3 getBottomPos() const { return _actor->getGlobalPose().p - physx::PxVec3(0, BODY_HY + BOARD_HY, 0); }
	inline physx::PxVec3 getBottomLeftPos() const { return _boardActor->getGlobalPose().p - physx::PxVec3(BOARD_HX, BOARD_HY, 0); }

	inline physx::PxVec3 getForwardDir() const { return _actor->getGlobalPose().q.rotate(physx::PxVec3(1, 0, 0)).getNormalized(); }

	physx::PxVec3 getShootingPos() const { return _actor->getGlobalPose().p + SHOOTING_POS_OFFSET * getForwardDir(); }
	physx::PxVec3 getShootingDir() const { return (getForwardDir() + SHOOTING_DIR_OFFSET).getNormalized(); }

	inline physx::PxVec3 getScarfPos() const { return _headActor->getGlobalPose().p - physx::PxVec3(0,HEAD_R,0); }

protected:
	physx::PxScene* _gScene;

	physx::PxAggregate* _aggregate;

	physx::PxRigidDynamic* _actor;  // cuerpo: actor principal
	physx::PxRigidDynamic* _headActor;
	physx::PxRigidDynamic* _boardActor;

	physx::PxMaterial* _playerMat;

	RenderItem* _bodyRI;
	RenderItem* _headRI;
	RenderItem* _boardRI;


protected:
	const physx::PxVec3 POS = { 0,0,0 };
	const physx::PxVec3 V = { 10, 0, 0 };
	const physx::PxVec3 W = { 10, 0, 0 };

	const float BODY_HX = .75f;
	const float	BODY_HY = 1.5f;
	const float	BODY_HZ = .75f;
	const float HEAD_R = .7f;
	const float BOARD_HX = 2.5f;
	const float BOARD_HY = .25f;
	const float BOARD_HZ = .75f;

	const physx::PxVec4 BODY_COLOR = { 0.5, 0.05, 0.15, 1 };
	const physx::PxVec4 HEAD_COLOR = { 0.7, 0.1, 0.3, 1 };
	const physx::PxVec4 BOARD_COLOR = { 0.2, 0.1, 0.1, 1 };

	const float SHOOTING_POS_OFFSET = 0.5f;
	const physx::PxVec3 SHOOTING_DIR_OFFSET = { 0.f, .15f, 0.f };
};

