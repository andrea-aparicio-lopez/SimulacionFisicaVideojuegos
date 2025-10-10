#include "Target.h"

using namespace physx;

Target::Target(PxVec3 pos, PxVec3 size)
	: tr(new PxTransform(pos))
{
	PxBoxGeometry geo = PxBoxGeometry(size.x,size.y,size.z);
	auto shape = CreateShape(geo);
	renderItem = new RenderItem(shape, tr, {1,0,1,1});
	RegisterRenderItem(renderItem);

}

Target::~Target() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}