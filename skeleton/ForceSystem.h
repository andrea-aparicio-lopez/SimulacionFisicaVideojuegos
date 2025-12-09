#pragma once
#include <list>

class ForceGenerator;

// Clase dueña de los generadores de fuerzas, 
// encargada de actualizarlos y borrarlos
class ForceSystem
{
public:
	ForceSystem();
	~ForceSystem();

	void addForceGen(ForceGenerator* gen);
	void update(double dt);

protected:
	std::list<ForceGenerator*> _forceGens;
};

