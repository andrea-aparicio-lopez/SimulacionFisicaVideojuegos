#pragma once
#include <vector>
#include "PxPhysicsAPI.h"

class RenderItem;

class Mountain
{
public:
    Mountain(const physx::PxVec3& position, float height = 50.f);

    ~Mountain();

    physx::PxTransform* getTr();

protected:
    RenderItem* _rItem;
    physx::PxTransform* _tr;

    const float DEPTH = 1.f;
    const physx::PxVec4 COLOR = { 0.2, 0.25, 0.35, 1. };
};
