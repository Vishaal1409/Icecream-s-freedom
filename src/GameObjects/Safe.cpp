#include "GameObjects/Safe.h"
#include "Game/Player.h"
#include "rlgl.h"

Safe::Safe(const std::string& name, Vector3 position, const std::string& code)
    : GameObject(name, position, true)
    , isOpen(false)
    , doorRotation(0.0f)
    , isOpening(false)
    , openProgress(0.0f)
    , openSpeed(2.0f)
    , correctCode(code)
    , currentInput("")
    , containedItemID("safe_diamond") {

    color = GRAY;
}

void Safe::Update(float deltaTime) {
    if (!isActive) return;

    UpdateAnimation(deltaTime);
}

void Safe::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? WHITE : color;

    // Draw safe body
    DrawCube(pos, 0.4f, 0.5f, 0.2f, renderColor);

    // Draw safe door
    rlPushMatrix();
    rlTranslatef(pos.x + 0.15f, pos.y, pos.z);
    rlRotatef(doorRotation, 0, 1, 0);
    rlTranslatef(-0.15f, 0, 0);
    DrawCube(pos, 0.3f, 0.45f, 0.15f, renderColor);
    rlPopMatrix();

    // Draw combination dial
    DrawCylinder({pos.x, pos.y - 0.15f, pos.z + 0.11f}, 0.08f, 0.08f, 0.05f, 12, DARKGRAY);

    // Draw lock mechanism indicator
    Color lockColor = isOpen ? GREEN : RED;
    DrawCube({pos.x - 0.15f, pos.y + 0.15f, pos.z + 0.11f}, 0.08f, 0.08f, 0.02f, lockColor);
}

void Safe::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive || isOpen) return;
    // Interaction handled by code input system
}

void Safe::AddDigit(char digit) {
    if (currentInput.length() < 4 && !isOpen) {
        currentInput += digit;
    }
}

void Safe::ClearInput() {
    currentInput.clear();
}

void Safe::SubmitCode() {
    if (currentInput.length() == 4) {
        CheckCode();
    }
}

void Safe::CheckCode() {
    if (currentInput == correctCode) {
        OpenSafe();
    }
    currentInput.clear();
}

void Safe::OpenSafe() {
    isOpen = true;
    isOpening = true;
    openProgress = 0.0f;
}

void Safe::UpdateAnimation(float deltaTime) {
    if (isOpening && openProgress < 1.0f) {
        openProgress += deltaTime * openSpeed;
        if (openProgress > 1.0f) {
            openProgress = 1.0f;
            isOpening = false;
        }
        doorRotation = openProgress * 110.0f;  // Rotate door 110 degrees
    }
}
