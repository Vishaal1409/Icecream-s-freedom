#include "Systems/InteractionSystem.h"
#include "Game/Player.h"
#include "raymath.h"
#include <algorithm>

InteractionSystem::InteractionSystem()
    : currentTarget(nullptr)
    , interactionRange(3.0f) {
}

void InteractionSystem::RegisterObject(GameObject* obj) {
    if (obj && obj->IsInteractable()) {
        gameObjects.push_back(obj);
    }
}

void InteractionSystem::UnregisterObject(GameObject* obj) {
    auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
    if (it != gameObjects.end()) {
        if (*it == currentTarget) {
            ClearTarget();
        }
        gameObjects.erase(it);
    }
}

void InteractionSystem::Update(Camera3D& camera) {
    // Clear previous target highlight
    if (currentTarget) {
        currentTarget->Unhighlight();
        currentTarget = nullptr;
    }

    // Perform raycast to find new target
    GameObject* newTarget = CheckRaycast(camera);

    if (newTarget) {
        currentTarget = newTarget;
        currentTarget->Highlight();
    }
}

GameObject* InteractionSystem::GetCurrentTarget() const {
    return currentTarget;
}

bool InteractionSystem::InteractWithTarget(Player* player) {
    if (currentTarget && currentTarget->IsActive()) {
        currentTarget->OnInteract(player);
        return true;
    }
    return false;
}

void InteractionSystem::ClearTarget() {
    if (currentTarget) {
        currentTarget->Unhighlight();
        currentTarget = nullptr;
    }
}

GameObject* InteractionSystem::CheckRaycast(Camera3D& camera) {
    // Create ray from camera forward
    Vector3 rayDirection = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    interactionRay.position = camera.position;
    interactionRay.direction = rayDirection;

    GameObject* closestObject = nullptr;
    float closestDistance = interactionRange;

    // Check all registered objects
    for (GameObject* obj : gameObjects) {
        if (!obj || !obj->IsActive() || !obj->IsInteractable()) continue;

        // Simple distance-based detection (more sophisticated collision could be added)
        float distance = DistanceToObject(obj, camera.position);

        if (distance <= interactionRange && distance < closestDistance) {
            // Check if object is roughly in front of camera (dot product check)
            Vector3 toObject = Vector3Normalize(Vector3Subtract(obj->GetTransform().GetPosition(), camera.position));
            float dot = Vector3DotProduct(rayDirection, toObject);

            if (dot > 0.9f) {  // Roughly facing the object (within ~25 degrees)
                closestObject = obj;
                closestDistance = distance;
            }
        }
    }

    return closestObject;
}

bool InteractionSystem::IsObjectInRange(const GameObject* obj, const Vector3& origin) const {
    return DistanceToObject(obj, origin) <= interactionRange;
}

float InteractionSystem::DistanceToObject(const GameObject* obj, const Vector3& origin) const {
    Vector3 objPos = obj->GetTransform().GetPosition();
    return Vector3Distance(origin, objPos);
}
