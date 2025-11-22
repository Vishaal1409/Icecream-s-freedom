#include "GameObjects/Door.h"
#include "Game/Player.h"
#include "raymath.h"

Door::Door(const std::string& name, Vector3 position, const std::string& keyID, bool exitDoor)
    : GameObject(name, position, true)
    , requiredKeyID(keyID)
    , isLocked(!keyID.empty())
    , isOpening(false)
    , isFullyOpen(false)
    , openProgress(0.0f)
    , openSpeed(1.0f)  // Takes 1 second to open
    , closedPosition(position)
    , openOffset({2.0f, 0, 0})  // Slide 2 units to the right
    , isExitDoor(exitDoor) {

    // Set color based on lock state
    color = isLocked ? BROWN : GREEN;
}

void Door::Update(float deltaTime) {
    if (!isActive) return;

    // Update opening animation
    if (isOpening && !isFullyOpen) {
        UpdateOpenAnimation(deltaTime);
    }
}

void Door::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? YELLOW : color;

    // Draw door frame
    DrawCube({pos.x, pos.y, pos.z}, 2.2f, 3.2f, 0.1f, DARKBROWN);

    // Draw door panel
    DrawCube({pos.x, pos.y, pos.z + 0.05f}, 2.0f, 3.0f, 0.08f, renderColor);

    // Draw door handle
    DrawSphere({pos.x + 0.8f, pos.y, pos.z + 0.15f}, 0.08f, GOLD);

    // Draw lock indicator if locked
    if (isLocked) {
        DrawCube({pos.x + 0.7f, pos.y + 0.2f, pos.z + 0.15f}, 0.15f, 0.2f, 0.08f, DARKGRAY);
    }
}

void Door::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive) return;

    if (isFullyOpen) {
        // Already open
        return;
    }

    if (!isLocked) {
        StartOpening();
        return;
    }

    // Door is locked - GameManager should have already checked for key and called Unlock()
    // If we reach here while still locked, that means no key was provided
}

void Door::Unlock() {
    isLocked = false;
    color = GREEN;
    // Auto-open after unlocking
    StartOpening();
}

void Door::StartOpening() {
    if (isOpening || isFullyOpen) return;

    isOpening = true;
    openProgress = 0.0f;
}

void Door::UpdateOpenAnimation(float deltaTime) {
    openProgress += deltaTime * openSpeed;

    if (openProgress >= 1.0f) {
        openProgress = 1.0f;
        isFullyOpen = true;
        isOpening = false;
    }

    // Interpolate position
    Vector3 newPos = {
        closedPosition.x + openOffset.x * openProgress,
        closedPosition.y + openOffset.y * openProgress,
        closedPosition.z + openOffset.z * openProgress
    };

    transform.SetPosition(newPos);
}
