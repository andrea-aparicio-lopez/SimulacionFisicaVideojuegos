#pragma once

#include <list>

class Player;
class Tree;
class Mountain;

class Forest
{
public:
	Forest(Player* player);
	~Forest();

	void update(double dt);

protected:
	Player* _player;
	std::list<Tree*> _trees;
	std::list<Mountain*> _mountains;

	float _fovX_trees_left = 80.f;
	float _fovX_trees_right = 160.f;

	float _fovX_mts_left = 300.f;
	float _fovX_mts_right = 800.f;
};

