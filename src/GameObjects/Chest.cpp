#include "GameObjects/Chest.h"
#include "Game/Player.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>

Chest::Chest(const std::string& name, Vector3 position, const std::string& keyID, const std::string& itemID)
    : GameObject(name, position, true)
    , requiredKeyID(keyID)
    , containedItemID(itemID)
    , isLocked(!keyID.empty())
    , isOpening(false)
    , isOpen(false)
    , openProgress(0.0f)
    , openSpeed(2.0f)  // Takes 0.5 seconds to open
    , lidRotation(0.0f) {

    color = BROWN;
}

void Chest::Update(float deltaTime) {
    if (!isActive) return;

    // Update opening animation
    if (isOpening && !isOpen) {
        UpdateOpenAnimation(deltaTime);
    }
}

void Chest::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? ORANGE : color;

    // Draw chest base
    DrawCube({pos.x, pos.y + 0.25f, pos.z}, 0.8f, 0.5f, 0.6f, renderColor);

    // Draw chest lid
    rlPushMatrix();
    rlTranslatef(pos.x, pos.y + 0.5f, pos.z - 0.3f);  // Hinge position
    rlRotatef(-lidRotation, 1, 0, 0);  // Rotate around X axis (hinge)
    rlTranslatef(0, 0, 0.3f);  // Offset back
    DrawCube({0, 0.05f, 0}, 0.8f, 0.1f, 0.6f, renderColor);
    rlPopMatrix();

    // Draw lock (if locked)
    if (isLocked) {
        DrawCube({pos.x, pos.y + 0.5f, pos.z + 0.32f}, 0.15f, 0.1f, 0.08f, GOLD);
    }

    // Draw metal straps
    DrawCube({pos.x, pos.y + 0.25f, pos.z + 0.28f}, 0.85f, 0.05f, 0.05f, DARKGRAY);
    DrawCube({pos.x, pos.y + 0.25f, pos.z - 0.28f}, 0.85f, 0.05f, 0.05f, DARKGRAY);
}

void Chest::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive) return;

    if (isOpen) {
        // Already opened and empty
        return;
    }

    if (!isLocked) {
        StartOpening();
        return;
    }

    // Chest is locked - GameManager should have already checked for key and called Unlock()
    // If we reach here while still locked, that means no key was provided
}

void Chest::Unlock() {
    isLocked = false;
    // Auto-open after unlocking
    StartOpening();
}

void Chest::StartOpening() {
    if (isOpening || isOpen) return;

    isOpening = true;
    openProgress = 0.0f;
}

void Chest::UpdateOpenAnimation(float deltaTime) {
    openProgress += deltaTime * openSpeed;

    if (openProgress >= 1.0f) {
        openProgress = 1.0f;
        isOpen = true;
        isOpening = false;
    }

    // Rotate lid from 0 to 90 degrees
    lidRotation = openProgress * 90.0f;

    // When fully open, give item to player
    if (isOpen && !containedItemID.empty()) {
        // Item will be given to player
        // (Will be implemented in Player class interaction)
    }
}
