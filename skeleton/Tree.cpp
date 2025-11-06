#include "Tree.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

using namespace physx;

Tree::Tree(const PxVec3& position, float trunkHeight, float trunkRadius,
        int foliageLayers, float foliageRadius)
        : _tr(new PxTransform(position))
    {
        // Colores
        Vector4 trunkColor(0.2f, 0.15f, 0.1f, 1.0f);
        Vector4 foliageColor(0.2f, 0.6f, 0.3f, 1.0f);

        // --- TRONCO ---
        PxCapsuleGeometry trunkGeo(trunkRadius, trunkHeight * 0.5f);
        PxShape* trunkShape = CreateShape(trunkGeo);
        PxQuat rot(PxPi / 2, PxVec3(0, 0, 1)); // rotación de 90º en eje Z
        PxTransform* trunkTransform = new PxTransform(position + PxVec3(0.0f, trunkHeight * 0.5f, 0.0f), rot);
        _partsTr.push_back(trunkTransform);
        _parts.push_back(new RenderItem(trunkShape, trunkTransform, trunkColor));

        // --- HOJAS ---
        float height = trunkHeight;
        for (int i = 0; i < foliageLayers; ++i)
        {
            float radius = foliageRadius * (1.0f - (float)i / foliageLayers);
            PxSphereGeometry foliageGeo(radius);
            PxShape* foliageShape = CreateShape(foliageGeo);

            height += (foliageRadius);
            PxTransform* foliageTransform = new PxTransform(position + PxVec3(0.0f, height, 0.0f));
            _partsTr.push_back(foliageTransform);
            _parts.push_back(new RenderItem(foliageShape, foliageTransform, foliageColor));
        }
    }

Tree::~Tree() {
    for (auto* p : _parts) p->release();
}

PxTransform* Tree::getTr() {
    return _tr;
}

std::vector<physx::PxTransform*> Tree::getPartsTr() {
    return _partsTr;
}