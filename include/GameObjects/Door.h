#pragma once

#include "Core/GameObject.h"

/**
 * Door Class - Demonstrates INHERITANCE and STATE MANAGEMENT
 *
 * A lockable door that can be opened with the correct key.
 * Shows POLYMORPHISM with door-specific behavior and state transitions.
 */
class Door : public GameObject {
private:
    // ENCAPSULATION - Private state management
    std::string requiredKeyID;
    bool isLocked;
    bool isOpening;
    bool isFullyOpen;
    float openProgress;  // 0.0 = closed, 1.0 = fully open
    float openSpeed;
    Vector3 closedPosition;
    Vector3 openOffset;
    bool isExitDoor;  // Win condition door

public:
    // Constructor
    Door(const std::string& name, Vector3 position, const std::string& keyID, bool exitDoor = false);

    // POLYMORPHISM - Override base class methods
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // ENCAPSULATION - Getters
    bool IsLocked() const { return isLocked; }
    bool IsOpen() const { return isFullyOpen; }
    bool IsExitDoor() const { return isExitDoor; }
    const std::string& GetRequiredKeyID() const { return requiredKeyID; }

    // Door unlocking (called by GameManager after key validation)
    void Unlock();

private:
    // ENCAPSULATION - Private helper methods
    void StartOpening();
    void UpdateOpenAnimation(float deltaTime);
};
