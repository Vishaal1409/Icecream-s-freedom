#pragma once

#include "raylib.h"

/**
 * CollisionSystem Class - Demonstrates ENCAPSULATION and SINGLE RESPONSIBILITY
 *
 * Handles all collision detection and resolution.
 * Keeps player within room boundaries.
 */
class CollisionSystem {
private:
    // ENCAPSULATION - Private members
    Vector3 roomMin;
    Vector3 roomMax;
    float playerRadius;

public:
    CollisionSystem(Vector3 min, Vector3 max, float radius = 0.5f);
    ~CollisionSystem() = default;

    // Check and correct position to stay within bounds
    Vector3 CheckBoundaries(const Vector3& position) const;

    // AABB collision check
    bool CheckAABB(Vector3 pos1, Vector3 size1, Vector3 pos2, Vector3 size2) const;

    // ENCAPSULATION - Getters/Setters
    void SetRoomBounds(Vector3 min, Vector3 max);
    void SetPlayerRadius(float radius) { playerRadius = radius; }
    float GetPlayerRadius() const { return playerRadius; }
};
