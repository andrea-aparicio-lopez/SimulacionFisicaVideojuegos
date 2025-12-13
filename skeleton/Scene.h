#pragma once

namespace physx {
	class PxTransform;
	class PxActor;
}

class Scene
{
protected:
	Scene();

public:
	virtual ~Scene() = 0;
	virtual void start() = 0;

	virtual void integrate(double dt) = 0;
	virtual void processKey(unsigned char key, const physx::PxTransform& camera) = 0;
	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {}
};

