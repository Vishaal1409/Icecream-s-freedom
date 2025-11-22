#pragma once

#include <string>
#include <memory>
#include "Transform.h"
#include "raylib.h"

// Forward declaration
class Player;

/**
 * GameObject - Abstract Base Class
 *
 * Demonstrates ABSTRACTION - Provides a common interface for all game objects.
 * Contains pure virtual functions that derived classes MUST implement.
 * This is the foundation of our OOP hierarchy.
 */
class GameObject {
protected:
    // ENCAPSULATION - Protected members accessible to derived classes
    std::string name;
    EntityTransform transform;
    bool isInteractable;
    bool isActive;
    Color color;
    bool isHighlighted;

public:
    // Constructor
    GameObject(const std::string& objectName, Vector3 position, bool interactable = false);

    // Virtual destructor - important for proper cleanup in inheritance hierarchy
    virtual ~GameObject() = default;

    // ABSTRACTION - Pure virtual functions (= 0 means derived classes MUST implement)
    // These define the INTERFACE that all game objects share
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnInteract(Player* player) = 0;

    // POLYMORPHISM - Virtual functions that can be overridden
    virtual void Highlight();
    virtual void Unhighlight();

    // ENCAPSULATION - Getter methods (const correctness)
    const std::string& GetName() const { return name; }
    EntityTransform& GetTransform() { return transform; }
    const EntityTransform& GetTransform() const { return transform; }
    bool IsInteractable() const { return isInteractable; }
    bool IsActive() const { return isActive; }
    bool IsHighlighted() const { return isHighlighted; }
    Color GetColor() const { return color; }

    // ENCAPSULATION - Setter methods with validation
    void SetActive(bool active) { isActive = active; }
    void SetInteractable(bool interactable) { isInteractable = interactable; }
    void SetColor(Color newColor) { color = newColor; }
};
