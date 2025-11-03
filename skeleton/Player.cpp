#include "Player.h"

using namespace physx;

Player::Player(PxVec3 pos)
	: Particle(pos, PxVec3(10, 0, 0), PxVec3(0), PxVec4(1, 0, 0, 1), 1.0, 50., 0., 0.)
{
	if (_renderItem != nullptr) {
		DeregisterRenderItem(_renderItem);
	}
	// Inicializar RenderItem
	PxBoxGeometry geo = PxBoxGeometry(1,2,1);
	auto shape = CreateShape(geo);
	_renderItem = new RenderItem(shape, _tr, _color);
	RegisterRenderItem(_renderItem);
}