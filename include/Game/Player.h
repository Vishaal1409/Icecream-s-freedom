#pragma once

#include "raylib.h"
#include "Systems/Inventory.h"
#include "Systems/CollisionSystem.h"
#include <memory>

/**
 * Player Class - Demonstrates COMPOSITION (HAS-A relationship)
 *
 * The player HAS-A camera, HAS-A inventory, and uses systems.
 * Shows composition over inheritance principle.
 */
class Player {
private:
    // COMPOSITION - Player HAS-A camera and inventory
    Camera3D camera;
    std::unique_ptr<Inventory> inventory;

    // Player state
    Vector3 velocity;
    float moveSpeed;
    float mouseSensitivity;
    bool controlsLocked;

    // References to systems (not owned by player)
    CollisionSystem* collisionSystem;

public:
    Player(Vector3 startPosition, CollisionSystem* collision);
    ~Player() = default;

    // Update and input handling
    void Update(float deltaTime);
    void HandleInput(float deltaTime);

    // COMPOSITION - Access to composed objects
    Camera3D& GetCamera() { return camera; }
    const Camera3D& GetCamera() const { return camera; }
    Inventory& GetInventory() { return *inventory; }
    const Inventory& GetInventory() const { return *inventory; }

    // Player state
    Vector3 GetPosition() const { return camera.position; }
    void SetPosition(Vector3 pos) { camera.position = pos; }
    void LockControls(bool locked) { controlsLocked = locked; }
    bool AreControlsLocked() const { return controlsLocked; }

    // Movement
    void Move(Vector3 direction, float deltaTime);

private:
    // ENCAPSULATION - Private helper methods
    void UpdateCameraMovement(float deltaTime);
    void UpdateMouseLook();
};
