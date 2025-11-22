#include "Systems/CollisionSystem.h"
#include "raymath.h"
#include <algorithm>

CollisionSystem::CollisionSystem(Vector3 min, Vector3 max, float radius)
    : roomMin(min)
    , roomMax(max)
    , playerRadius(radius) {
}

Vector3 CollisionSystem::CheckBoundaries(const Vector3& position) const {
    Vector3 correctedPos = position;

    // Clamp position within room bounds (with player radius offset)
    correctedPos.x = std::max(roomMin.x + playerRadius, std::min(roomMax.x - playerRadius, position.x));
    correctedPos.y = std::max(roomMin.y, std::min(roomMax.y, position.y));
    correctedPos.z = std::max(roomMin.z + playerRadius, std::min(roomMax.z - playerRadius, position.z));

    return correctedPos;
}

bool CollisionSystem::CheckAABB(Vector3 pos1, Vector3 size1, Vector3 pos2, Vector3 size2) const {
    // Simple AABB (Axis-Aligned Bounding Box) collision detection
    return (pos1.x - size1.x / 2 < pos2.x + size2.x / 2 &&
            pos1.x + size1.x / 2 > pos2.x - size2.x / 2 &&
            pos1.y - size1.y / 2 < pos2.y + size2.y / 2 &&
            pos1.y + size1.y / 2 > pos2.y - size2.y / 2 &&
            pos1.z - size1.z / 2 < pos2.z + size2.z / 2 &&
            pos1.z + size1.z / 2 > pos2.z - size2.z / 2);
}

void CollisionSystem::SetRoomBounds(Vector3 min, Vector3 max) {
    roomMin = min;
    roomMax = max;
}
