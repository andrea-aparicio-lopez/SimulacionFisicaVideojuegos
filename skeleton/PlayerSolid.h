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

	physx::PxMaterial* _playerMat;

	RenderItem* _bodyRI;
	RenderItem* _headRI;
	RenderItem* _boardRI;


protected:
	const physx::PxVec3 POS = { 0,0,0 };
	const physx::PxVec3 V = { 10, 0, 0 };
	const physx::PxVec3 W = { 10, 0, 0 };	// w o fuerza y fricción?

	const float BODY_HX = .5f;
	const float	BODY_HY = 1.f;
	const float	BODY_HZ = .5f;
	const float HEAD_R = .25f;

	const physx::PxVec4 BODY_COLOR = { 0.3, 0.55, 0.3, 1 };
	const physx::PxVec4 HEAD_COLOR = { 0.3, 0.3, 0.55, 1 };
	const physx::PxVec4 BOARD_COLOR = { 0.3, 0.55, 0.3, 1 };


};

