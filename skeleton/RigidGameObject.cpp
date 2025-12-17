#include "RigidGameObject.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "GaussianGen.h"

#include <iostream>

RigidGameObject::RigidGameObject() {

}

RigidGameObject::~RigidGameObject() {
	if (_renderItem != nullptr) _renderItem->release();

	if (_actor->userData != nullptr) {
		delete _actor->userData;
		_actor->userData = nullptr;
	}

	delete _explSys;
	delete _explForceGen;
}

void RigidGameObject::update(double dt) {
	if (!_alive && _actor != nullptr) {
		_actor->release();
		_actor = nullptr;

		_renderItem->release();
		_renderItem = nullptr;
	}

	_explSys->update(dt);
	if (_explPartGen->isActive()) _explPartGen->setActive(false);

}