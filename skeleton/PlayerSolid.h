#pragma once
#include <PxPhysicsAPI.h>

class RenderItem;

class PlayerSolid
{
public:
	PlayerSolid(physx::PxScene* gScene, physx::PxPhysics* gPhysics, physx::PxVec3 pos);
	~PlayerSolid();

	inline physx::PxRigidDynamic* getActor() { return _actor; }

protected:
	physx::PxScene* _gScene;

	physx::PxRigidDynamic* _actor;
	physx::PxRigidDynamic* _headActor;
	physx::PxRigidDynamic* _boardActor;

	physx::PxMaterial* _playerMat;

	RenderItem* _bodyRI;
	RenderItem* _headRI;
	RenderItem* _boardRI;


protected:
	const physx::PxVec3 POS = { 0,0,0 };
	const physx::PxVec3 V = { 10, 0, 0 };
	const physx::PxVec3 W = { 10, 0, 0 };	// w o fuerza y fricción?

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


};

