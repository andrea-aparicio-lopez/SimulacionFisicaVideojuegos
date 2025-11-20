#include "Target.h"

using namespace physx;

Target::Target(PxVec3 pos, PxVec3 size, PxVec4 color)
	: tr(new PxTransform(pos))
{
	PxBoxGeometry geo = PxBoxGeometry(size.x,size.y,size.z);
	PxShape* shape = CreateShape(geo);
	renderItem = new RenderItem(shape, tr, color);
	RegisterRenderItem(renderItem);

}

Target::~Target() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}