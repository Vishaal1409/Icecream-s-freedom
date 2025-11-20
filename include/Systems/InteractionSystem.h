#pragma once

#include "Core/GameObject.h"
#include "raylib.h"
#include <vector>
#include <memory>

// Forward declaration
class Player;

/**
 * InteractionSystem Class - Demonstrates SINGLE RESPONSIBILITY PRINCIPLE
 *
 * Handles raycasting and interaction detection.
 * Separated into its own class following good OOP design.
 */
class InteractionSystem {
private:
    // ENCAPSULATION - Private members
    std::vector<GameObject*> gameObjects;
    GameObject* currentTarget;
    float interactionRange;
    Ray interactionRay;

public:
    InteractionSystem();
    ~InteractionSystem() = default;

    // Public interface
    void RegisterObject(GameObject* obj);
    void UnregisterObject(GameObject* obj);
    void Update(Camera3D& camera);
    GameObject* GetCurrentTarget() const;
    bool InteractWithTarget(Player* player);
    void ClearTarget();

    // ENCAPSULATION - Getters/Setters
    float GetInteractionRange() const { return interactionRange; }
    void SetInteractionRange(float range) { interactionRange = range; }

private:
    // ENCAPSULATION - Private helper methods
    GameObject* CheckRaycast(Camera3D& camera);
    bool IsObjectInRange(const GameObject* obj, const Vector3& origin) const;
    float DistanceToObject(const GameObject* obj, const Vector3& origin) const;
};
