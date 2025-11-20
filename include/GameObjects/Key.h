#pragma once

#include "Core/GameObject.h"

/**
 * Key Class - Demonstrates INHERITANCE
 *
 * Inherits from GameObject base class and implements its pure virtual functions.
 * Shows POLYMORPHISM by providing Key-specific behavior for Update, Render, and OnInteract.
 */
class Key : public GameObject {
private:
    // ENCAPSULATION - Private member variables
    std::string keyID;
    bool isCollected;
    float rotationSpeed;
    float bobSpeed;
    float bobHeight;
    float bobTimer;
    float baseY;

public:
    // Constructor
    Key(const std::string& id, Vector3 position, Color keyColor = GOLD);

    // POLYMORPHISM - Override base class pure virtual functions
    // Each game object type provides its own implementation
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // ENCAPSULATION - Getter methods
    const std::string& GetKeyID() const { return keyID; }
    bool IsCollected() const { return isCollected; }

    // Override highlight for keys (make them glow more)
    void Highlight() override;
    void Unhighlight() override;

private:
    // ENCAPSULATION - Private helper methods
    void AnimateSpin(float deltaTime);
    void AnimateBob(float deltaTime);
};
