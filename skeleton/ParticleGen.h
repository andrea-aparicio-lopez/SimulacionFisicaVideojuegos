#pragma once

namespace physx {
	class PxVec3;
}

class ParticleGen
{
protected:
	ParticleGen();

public:
	virtual ~ParticleGen() = 0;

	virtual void generateP() = 0;


protected:

};

