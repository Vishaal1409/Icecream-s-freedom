#include "Core/Transform.h"
#include "raymath.h"
#include <cmath>

EntityTransform::EntityTransform()
    : position({0, 0, 0}), rotation({0, 0, 0}), scale({1, 1, 1}) {
}

EntityTransform::EntityTransform(Vector3 pos, Vector3 rot, Vector3 scl)
    : position(pos), rotation(rot), scale(scl) {
}

void EntityTransform::Translate(Vector3 delta) {
    position = Vector3Add(position, delta);
}

void EntityTransform::Rotate(Vector3 delta) {
    rotation = Vector3Add(rotation, delta);
}

Vector3 EntityTransform::Forward() const {
    // Calculate forward vector from Y rotation (yaw)
    float yawRad = rotation.y * DEG2RAD;
    return {
        sinf(yawRad),
        0.0f,
        cosf(yawRad)
    };
}

Vector3 EntityTransform::Right() const {
    // Calculate right vector from Y rotation (yaw)
    float yawRad = rotation.y * DEG2RAD;
    return {
        cosf(yawRad),
        0.0f,
        -sinf(yawRad)
    };
}

Vector3 EntityTransform::Up() const {
    return {0, 1, 0};
}
