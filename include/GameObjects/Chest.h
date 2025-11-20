#pragma once

#include "Core/GameObject.h"
#include <string>

/**
 * Chest Class - Demonstrates INHERITANCE and STATE MANAGEMENT
 *
 * A lockable chest that contains items (keys).
 * Shows POLYMORPHISM with complex state transitions and animations.
 */
class Chest : public GameObject {
private:
    // ENCAPSULATION - Private state management
    std::string requiredKeyID;
    std::string containedItemID;  // What's inside the chest
    bool isLocked;
    bool isOpening;
    bool isOpen;
    float openProgress;  // 0.0 = closed, 1.0 = fully open
    float openSpeed;
    float lidRotation;   // Rotation angle of the lid

public:
    // Constructor
    Chest(const std::string& name, Vector3 position, const std::string& keyID, const std::string& itemID);

    // POLYMORPHISM - Override base class methods
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // ENCAPSULATION - Getters
    bool IsLocked() const { return isLocked; }
    bool IsOpen() const { return isOpen; }
    const std::string& GetRequiredKeyID() const { return requiredKeyID; }
    const std::string& GetContainedItemID() const { return containedItemID; }

    // Chest unlocking (called by GameManager after key validation)
    void Unlock();

private:
    // ENCAPSULATION - Private helper methods
    void StartOpening();
    void UpdateOpenAnimation(float deltaTime);
};
