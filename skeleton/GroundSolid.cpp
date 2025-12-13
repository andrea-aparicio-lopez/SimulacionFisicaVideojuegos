#include "GroundSolid.h"
#include "RenderUtils.hpp"
#include "GameObjectData.h"

using namespace physx;

GroundSolid::GroundSolid(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos, PxVec3 h, PxVec4 color)
{
	auto mat = gPhysics->createMaterial(0.2f, 0.f, 0.95f);

	auto tr = PxTransform(pos);
	auto geo = PxBoxGeometry(h);
	auto shape = CreateShape(geo, mat);
	_actor = gPhysics->createRigidStatic(tr);
	_actor->attachShape(*shape);

	GameObjectData* data = new GameObjectData();
	data->type = GameObjectType::Ground;
	data->object = this;
	_actor->userData = data;

	_renderItem = new RenderItem(shape, _actor, color);
	gScene->addActor(*_actor);
}

GroundSolid::~GroundSolid() {
	_renderItem->release();
	_actor->getScene()->removeActor(*_actor);
}