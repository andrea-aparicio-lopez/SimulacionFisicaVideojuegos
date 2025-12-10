#include "GroundSolid.h"
#include "RenderUtils.hpp"

using namespace physx;

GroundSolid::GroundSolid(PxScene* gScene, PxPhysics* gPhysics, PxVec3 pos, PxVec3 h, PxVec4 color)
{
	auto tr = PxTransform(pos);
	auto geo = PxBoxGeometry(h);
	auto shape = CreateShape(geo);
	_actor = gPhysics->createRigidStatic(tr);
	_actor->attachShape(*shape);

	_renderItem = new RenderItem(shape, _actor, color);
	gScene->addActor(*_actor);
}

GroundSolid::~GroundSolid() {
	_renderItem->release();
	_actor->getScene()->removeActor(*_actor);
}