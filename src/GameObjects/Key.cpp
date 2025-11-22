#include "GameObjects/Key.h"
#include "Game/Player.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>

Key::Key(const std::string& id, Vector3 position, Color keyColor)
    : GameObject("Key_" + id, position, true)
    , keyID(id)
    , isCollected(false)
    , rotationSpeed(90.0f)  // 90 degrees per second
    , bobSpeed(2.0f)        // 2 second period
    , bobHeight(0.1f)       // 0.1 units up and down
    , bobTimer(0.0f)
    , baseY(position.y) {

    color = keyColor;
}

void Key::Update(float deltaTime) {
    if (isCollected || !isActive) return;

    // POLYMORPHISM - Key-specific update behavior
    AnimateSpin(deltaTime);
    AnimateBob(deltaTime);
}

void Key::Render() {
    if (isCollected || !isActive) return;

    Vector3 pos = transform.GetPosition();
    Vector3 rot = transform.GetRotation();

    // Draw key using simple 3D primitives
    // Key consists of: ring (head) + shaft + teeth

    Color renderColor = isHighlighted ? YELLOW : color;

    // Save current matrix
    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    rlRotatef(rot.y, 0, 1, 0);

    // Key ring (head) - torus approximation using cylinder
    DrawCylinder({0, 0, 0}, 0.15f, 0.15f, 0.05f, 16, renderColor);

    // Key shaft
    DrawCylinder({0, -0.2f, 0}, 0.03f, 0.03f, 0.4f, 8, renderColor);

    // Key teeth (simple boxes)
    DrawCube({0.04f, -0.38f, 0}, 0.08f, 0.05f, 0.03f, renderColor);
    DrawCube({-0.04f, -0.36f, 0}, 0.08f, 0.05f, 0.03f, renderColor);

    rlPopMatrix();
}

void Key::OnInteract([[maybe_unused]] Player* player) {
    if (isCollected || !isActive) return;

    // POLYMORPHISM - Key-specific interaction behavior
    // Add key to player's inventory
    isCollected = true;
    isActive = false;

    // Player will handle adding to inventory (we'll implement this in Player class)
}

void Key::Highlight() {
    GameObject::Highlight();
    // Keys glow when highlighted
}

void Key::Unhighlight() {
    GameObject::Unhighlight();
}

// ENCAPSULATION - Private helper methods
void Key::AnimateSpin(float deltaTime) {
    Vector3 rot = transform.GetRotation();
    rot.y += rotationSpeed * deltaTime;
    if (rot.y >= 360.0f) rot.y -= 360.0f;
    transform.SetRotation(rot);
}

void Key::AnimateBob(float deltaTime) {
    bobTimer += deltaTime * bobSpeed;

    Vector3 pos = transform.GetPosition();
    pos.y = baseY + sinf(bobTimer * PI) * bobHeight;
    transform.SetPosition(pos);
}
