#pragma once

#include <list>

class Tree;
class Player;

class Forest
{
public:
	Forest(Player* player);
	~Forest();

	void update(double dt);

protected:
	Player* _player;
	std::list<Tree*> _trees;

	float _fovX = 100.f;
};

