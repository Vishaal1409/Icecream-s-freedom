#include "Core/GameObject.h"

GameObject::GameObject(const std::string& objectName, Vector3 position, bool interactable)
    : name(objectName)
    , transform(position)
    , isInteractable(interactable)
    , isActive(true)
    , color(WHITE)
    , isHighlighted(false) {
}

void GameObject::Highlight() {
    isHighlighted = true;
    // Default highlight: brighten the color slightly
    // Derived classes can override for different highlight effects
}

void GameObject::Unhighlight() {
    isHighlighted = false;
}
