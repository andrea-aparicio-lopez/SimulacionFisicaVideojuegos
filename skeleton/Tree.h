#pragma once
#include <vector>
#include "PxPhysicsAPI.h"

class RenderItem;

class Tree
{
public:
    Tree(const physx::PxVec3& position, float trunkHeight = 5.0f, float trunkRadius = 0.3f,
        int foliageLayers = 3, float foliageRadius = 2.0f);

    ~Tree();

    physx::PxTransform* getTr();
    std::vector<physx::PxTransform*> getPartsTr();
    //void updateTr

protected:
    std::vector<RenderItem*> _parts;
    std::vector<physx::PxTransform*> _partsTr;
    physx::PxTransform* _tr;
};
