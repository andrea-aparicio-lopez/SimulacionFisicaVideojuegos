#pragma once

#include <vector>

class Particle;

class Axis
{
public:
	Axis();
	~Axis();

protected:
	std::vector<Particle*> _axis;
};

