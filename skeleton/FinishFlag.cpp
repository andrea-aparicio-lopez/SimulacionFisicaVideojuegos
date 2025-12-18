#include "FinishFlag.h"
#include "RenderUtils.hpp"

using namespace physx;

FinishFlag::FinishFlag(const PxVec3& position)
    //: _tr(PxTransform(position))
{

    // ---------- POLE ------------
    PxCapsuleGeometry poleGeo = PxCapsuleGeometry(poleRadius, poleHeight * 0.5f);
    PxShape* poleShape = CreateShape(poleGeo);

    PxQuat poleRot(PxPi / 2, PxVec3(0, 0, 1)); // capsule vertical
    PxTransform* poleTr = new PxTransform(position + PxVec3(0.0f, poleHeight * 0.5f, 0.0f), poleRot);

    _partsTr.push_back(poleTr);
    _rItems.push_back(new RenderItem(poleShape, poleTr, poleColor));


    // ---------- FLAG ------------

    PxBoxGeometry cellGeo(cellL * 0.5f, cellL * 0.5f, 0.01f);

    PxVec3 flagOrigin = position + PxVec3(poleRadius + cellL * checkerCols * 0.5f,
                                    poleHeight - cellL * checkerRows * 0.5f,
                                    0.0f);

    for (int y = 0; y < checkerRows; ++y)
    {
        for (int x = 0; x < checkerCols; ++x)
        {
            bool isWhite = ((x + y) % 2) == 0;
            Vector4 color = isWhite ? white : black;

            PxShape* cellShape = CreateShape(cellGeo);

            PxVec3 offset(
                (x - checkerCols * 0.5f + 0.5f) * cellL,
                (checkerRows * 0.5f - y - 0.5f) * cellL,
                0.0f
            );

            PxTransform* cellTr = new PxTransform(flagOrigin + offset);
            _partsTr.push_back(cellTr);
            _rItems.push_back(new RenderItem(cellShape, cellTr, color));
        }
    }
}

FinishFlag::~FinishFlag() {
    for (auto ri : _rItems)
        ri->release();
}