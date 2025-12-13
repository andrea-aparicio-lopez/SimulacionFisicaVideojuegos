#pragma once

enum class GameObjectType {
	PlayerBody,
	PlayerHead,
	PlayerBoard,
	Ground,
	Obstacle,
	Snowball
};

struct GameObjectData {
public:
	GameObjectType type;
	void* object;
};