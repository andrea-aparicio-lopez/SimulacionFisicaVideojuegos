#include "Forest.h"
#include "Player.h"
#include "Tree.h"
#include "Mountain.h"
#include "RenderUtils.hpp"

using namespace physx;

Forest::Forest(Player* player)
	: _player(player)
{
	auto playerPos = PxVec3(_player->getPos().x, 0, _player->getPos().z);

	// ARBOLES
	_trees.push_back(new Tree(playerPos + PxVec3(-80, 0, -40), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(-60, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(-45, 0, -35), 2.0f, 0.3f, 4, 2.0));

	_trees.push_back(new Tree(playerPos + PxVec3(-38, 0, -20), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(-24, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(-10, 0, -25), 2.0f, 0.3f, 4, 2.0));


	_trees.push_back(new Tree(playerPos + PxVec3(10, 0, -40), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(20, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(30, 0, -35), 2.0f, 0.3f, 4, 2.0));

	_trees.push_back(new Tree(playerPos + PxVec3(45, 0, -20), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(53, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(60, 0, -25), 2.0f, 0.3f, 4, 2.0));

	_trees.push_back(new Tree(playerPos + PxVec3(65, 0, -45), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(72, 0, -40), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(78, 0, -25), 2.0f, 0.3f, 4, 2.0));

	_trees.push_back(new Tree(playerPos + PxVec3(90, 0, -40), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(93, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(100, 0, -35), 2.0f, 0.3f, 4, 2.0));

	_trees.push_back(new Tree(playerPos + PxVec3(112, 0, -20), 3.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(120, 0, -30), 3.0f, 0.3f, 5, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(128, 0, -50), 2.0f, 0.3f, 4, 2.0));
	_trees.push_back(new Tree(playerPos + PxVec3(135, 0, -25), 2.0f, 0.3f, 4, 2.0));


	// MONTAÑAS
	_mountains.push_back(new Mountain(playerPos + PxVec3(-80, 0, -180)));
	_mountains.push_back(new Mountain(playerPos + PxVec3(-5, 0, -300), 70));
	_mountains.push_back(new Mountain(playerPos + PxVec3(85, 0, -100), 25));
	_mountains.push_back(new Mountain(playerPos + PxVec3(147, 0, -120), 35));
	_mountains.push_back(new Mountain(playerPos + PxVec3(220, 0, -280), 80));

	_mountains.push_back(new Mountain(playerPos + PxVec3(300, 0, -160), 45));
	_mountains.push_back(new Mountain(playerPos + PxVec3(370, 0, -300), 70));
	_mountains.push_back(new Mountain(playerPos + PxVec3(438, 0, -100), 25));
	_mountains.push_back(new Mountain(playerPos + PxVec3(508, 0, -120), 35));
	_mountains.push_back(new Mountain(playerPos + PxVec3(590, 0, -280), 80));

	_mountains.push_back(new Mountain(playerPos + PxVec3(660, 0, -155), 45));
	_mountains.push_back(new Mountain(playerPos + PxVec3(720, 0, -130), 30));
	_mountains.push_back(new Mountain(playerPos + PxVec3(785, 0, -210), 60));
	_mountains.push_back(new Mountain(playerPos + PxVec3(850, 0, -200)));
}

Forest::~Forest() {
	for (auto t : _trees)
		delete t;
}

void Forest::update(double dt) {
	auto playerPos = _player->getPos();

	for (auto t : _trees) {
		PxTransform* tr = t->getTr();
		if (tr->p.x < playerPos.x - _fovX_trees_left) {
			tr->p = PxVec3(playerPos.x + _fovX_trees_right, tr->p.y, tr->p.z);
			for (auto itemTr : t->getPartsTr())
				itemTr->p = PxVec3(tr->p.x, itemTr->p.y, itemTr->p.z);
		}
	}

	for (auto mt : _mountains) {
		PxTransform* tr = mt->getTr();
		if (tr->p.x < playerPos.x - _fovX_mts_left) {
			tr->p = PxVec3(playerPos.x + _fovX_mts_right, tr->p.y, tr->p.z);
		}
	}
}