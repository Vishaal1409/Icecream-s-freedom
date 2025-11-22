#pragma once

#include "raylib.h"

/**
 * EntityTransform Component
 *
 * Demonstrates ENCAPSULATION - Wraps position, rotation, and scale data
 * with controlled access through getter/setter methods.
 */
class EntityTransform {
private:
    Vector3 position;
    Vector3 rotation;  // Euler angles in degrees
    Vector3 scale;

public:
    EntityTransform();
    EntityTransform(Vector3 pos, Vector3 rot = {0, 0, 0}, Vector3 scl = {1, 1, 1});

    // Getters - ENCAPSULATION principle (read-only access to private data)
    Vector3 GetPosition() const { return position; }
    Vector3 GetRotation() const { return rotation; }
    Vector3 GetScale() const { return scale; }

    // Setters - ENCAPSULATION principle (controlled write access)
    void SetPosition(Vector3 pos) { position = pos; }
    void SetRotation(Vector3 rot) { rotation = rot; }
    void SetScale(Vector3 scl) { scale = scl; }

    // Utility methods
    void Translate(Vector3 delta);
    void Rotate(Vector3 delta);
    Vector3 Forward() const;
    Vector3 Right() const;
    Vector3 Up() const;
};
