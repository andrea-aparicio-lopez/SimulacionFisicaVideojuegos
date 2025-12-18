#include <vector>
#include "PxPhysicsAPI.h"

class RenderItem;

class FinishFlag
{
public:
    FinishFlag(const physx::PxVec3& position);

    ~FinishFlag();

    physx::PxTransform& getTr();

protected:
    std::vector<physx::PxTransform*> _partsTr;
    std::vector<RenderItem*> _rItems;

    const float poleHeight = 12.f;
    const float poleRadius = .3f;
    const float cellL = .75f;
    const int checkerCols = 6;
    const int checkerRows = 4;

    const physx::PxVec4 poleColor = { 0.25f, 0.15f, 0.1f, 1.0f };
    const physx::PxVec4 white = { 0.95, 0.95, 0.95, 1. };
    const physx::PxVec4 black = { 0.0f, 0.0f, 0.0f, 1.0f };
};
