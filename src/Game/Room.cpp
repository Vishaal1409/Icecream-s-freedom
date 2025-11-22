#include "Game/Room.h"

Room::Room(float w, float h, float d)
    : width(w)
    , height(h)
    , depth(d)
    , center({0, h / 2, 0})
    , floorColor(GRAY)
    , wallColor(LIGHTGRAY)
    , ceilingColor(DARKGRAY) {
}

void Room::Render() {
    RenderFloor();
    RenderCeiling();
    RenderWalls();
    RenderDecorations();
}

Vector3 Room::GetMin() const {
    return {-width / 2, 0, -depth / 2};
}

Vector3 Room::GetMax() const {
    return {width / 2, height, depth / 2};
}

void Room::RenderFloor() {
    DrawPlane({0, 0, 0}, {width, depth}, floorColor);

    // Grid lines for visual interest
    for (float x = -width / 2; x <= width / 2; x += 1.0f) {
        DrawLine3D({x, 0.01f, -depth / 2}, {x, 0.01f, depth / 2}, DARKGRAY);
    }
    for (float z = -depth / 2; z <= depth / 2; z += 1.0f) {
        DrawLine3D({-width / 2, 0.01f, z}, {width / 2, 0.01f, z}, DARKGRAY);
    }
}

void Room::RenderCeiling() {
    // Draw ceiling
    Vector3 corners[4] = {
        {-width / 2, height, -depth / 2},
        {width / 2, height, -depth / 2},
        {width / 2, height, depth / 2},
        {-width / 2, height, depth / 2}
    };

    DrawTriangle3D(corners[0], corners[1], corners[2], ceilingColor);
    DrawTriangle3D(corners[0], corners[2], corners[3], ceilingColor);
}

void Room::RenderWalls() {
    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    // North wall (-Z)
    DrawCube({0, height / 2, -halfDepth}, width, height, 0.1f, wallColor);

    // South wall (+Z)
    DrawCube({0, height / 2, halfDepth}, width, height, 0.1f, wallColor);

    // West wall (-X)
    DrawCube({-halfWidth, height / 2, 0}, 0.1f, height, depth, wallColor);

    // East wall (+X)
    DrawCube({halfWidth, height / 2, 0}, 0.1f, height, depth, wallColor);
}

void Room::RenderDecorations() {
    // Table (decorative, not interactable)
    Vector3 tablePos = {-3, 0, -2};
    DrawCube({tablePos.x, tablePos.y + 0.35f, tablePos.z}, 1.5f, 0.7f, 1.0f, BROWN);

    // Table legs
    float legHeight = 0.7f;
    float legSize = 0.1f;
    DrawCube({tablePos.x - 0.65f, legHeight / 2, tablePos.z - 0.4f}, legSize, legHeight, legSize, DARKBROWN);
    DrawCube({tablePos.x + 0.65f, legHeight / 2, tablePos.z - 0.4f}, legSize, legHeight, legSize, DARKBROWN);
    DrawCube({tablePos.x - 0.65f, legHeight / 2, tablePos.z + 0.4f}, legSize, legHeight, legSize, DARKBROWN);
    DrawCube({tablePos.x + 0.65f, legHeight / 2, tablePos.z + 0.4f}, legSize, legHeight, legSize, DARKBROWN);

    // Shelf
    Vector3 shelfPos = {3, 0, 2};
    for (int i = 0; i < 3; i++) {
        DrawCube({shelfPos.x, shelfPos.y + 0.3f + i * 0.4f, shelfPos.z}, 1.2f, 0.05f, 0.4f, DARKBROWN);
    }

    // Picture frames on wall
    DrawCube({-2, 1.5f, -4.9f}, 0.6f, 0.8f, 0.05f, DARKGRAY);
    DrawCube({-2, 1.5f, -4.85f}, 0.5f, 0.7f, 0.02f, Color{106, 90, 74, 255});

    DrawCube({1, 1.8f, -4.9f}, 0.6f, 0.8f, 0.05f, DARKGRAY);
    DrawCube({1, 1.8f, -4.85f}, 0.5f, 0.7f, 0.02f, Color{106, 90, 74, 255});
}
