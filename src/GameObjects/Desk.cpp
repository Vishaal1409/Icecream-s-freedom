#include "GameObjects/Desk.h"
#include "Game/Player.h"

Desk::Desk(const std::string& name, Vector3 position)
    : GameObject(name, position, true)
    , drawer1OpenProgress(0.0f)
    , drawer2OpenProgress(0.0f)
    , drawer1Open(false)
    , drawer2Open(false)
    , drawerSpeed(3.0f)
    , hiddenItemID("desk_key")
    , itemCollected(false) {

    color = BROWN;
}

void Desk::Update(float deltaTime) {
    if (!isActive) return;

    UpdateDrawerAnimation(deltaTime);
}

void Desk::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? ORANGE : color;

    // Draw main desk surface
    DrawCube({pos.x, pos.y + 0.4f, pos.z}, 0.8f, 0.8f, 0.5f, renderColor);

    // Draw left drawer
    Vector3 leftDrawerPos = {pos.x - 0.25f, pos.y + 0.15f, pos.z};
    leftDrawerPos.z += drawer1OpenProgress * 0.3f;  // Slide out
    DrawCube(leftDrawerPos, 0.3f, 0.3f, 0.3f, DARKGRAY);

    // Draw right drawer
    Vector3 rightDrawerPos = {pos.x + 0.25f, pos.y + 0.15f, pos.z};
    rightDrawerPos.z += drawer2OpenProgress * 0.3f;  // Slide out
    DrawCube(rightDrawerPos, 0.3f, 0.3f, 0.3f, DARKGRAY);

    // Draw 4 legs
    float legSize = 0.05f;
    DrawCube({pos.x - 0.3f, pos.y - 0.2f, pos.z - 0.2f}, legSize, 0.4f, legSize, DARKBROWN);
    DrawCube({pos.x + 0.3f, pos.y - 0.2f, pos.z - 0.2f}, legSize, 0.4f, legSize, DARKBROWN);
    DrawCube({pos.x - 0.3f, pos.y - 0.2f, pos.z + 0.2f}, legSize, 0.4f, legSize, DARKBROWN);
    DrawCube({pos.x + 0.3f, pos.y - 0.2f, pos.z + 0.2f}, legSize, 0.4f, legSize, DARKBROWN);
}

void Desk::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive) return;

    // Toggle first available drawer
    if (!drawer1Open) {
        ToggleDrawer1();
    } else if (!drawer2Open) {
        ToggleDrawer2();
    }
}

void Desk::ToggleDrawer1() {
    drawer1Open = !drawer1Open;
}

void Desk::ToggleDrawer2() {
    drawer2Open = !drawer2Open;
}

void Desk::UpdateDrawerAnimation(float deltaTime) {
    // Animate drawer 1
    if (drawer1Open && drawer1OpenProgress < 1.0f) {
        drawer1OpenProgress += deltaTime * drawerSpeed;
        if (drawer1OpenProgress > 1.0f) drawer1OpenProgress = 1.0f;
    } else if (!drawer1Open && drawer1OpenProgress > 0.0f) {
        drawer1OpenProgress -= deltaTime * drawerSpeed;
        if (drawer1OpenProgress < 0.0f) drawer1OpenProgress = 0.0f;
    }

    // Animate drawer 2
    if (drawer2Open && drawer2OpenProgress < 1.0f) {
        drawer2OpenProgress += deltaTime * drawerSpeed;
        if (drawer2OpenProgress > 1.0f) drawer2OpenProgress = 1.0f;
    } else if (!drawer2Open && drawer2OpenProgress > 0.0f) {
        drawer2OpenProgress -= deltaTime * drawerSpeed;
        if (drawer2OpenProgress < 0.0f) drawer2OpenProgress = 0.0f;
    }
}
