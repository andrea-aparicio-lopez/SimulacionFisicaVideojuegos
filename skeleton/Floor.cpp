#include "Floor.h"

using namespace physx;

Floor::Floor(PxVec3 pos, PxVec4 color)
	: tr(new PxTransform(pos))
{
	auto floorGeo = PxBoxGeometry(1000, 0.01, 1000);
	auto floorShape = CreateShape(floorGeo);
	renderItem = new RenderItem(floorShape, tr, color);
	RegisterRenderItem(renderItem);
}

Floor::~Floor() {
	DeregisterRenderItem(renderItem);
}