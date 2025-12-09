#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem() {}

ForceSystem::~ForceSystem() {
	for (auto gen : _forceGens)
		delete gen;
}

void ForceSystem::addForceGen(ForceGenerator* gen) {
	_forceGens.push_back(gen);
}

void ForceSystem::update(double dt) {
	for (auto gen : _forceGens)
		gen->update(dt);
}