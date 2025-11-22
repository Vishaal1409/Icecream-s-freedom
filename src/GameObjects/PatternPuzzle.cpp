#include "GameObjects/PatternPuzzle.h"
#include "Game/Player.h"
#include "rlgl.h"

PatternPuzzle::PatternPuzzle(const std::string& name, Vector3 position)
    : GameObject(name, position, true)
    , isActive_input(false)
    , isSolved(false) {

    color = SKYBLUE;

    // Setup correct pattern
    for (int i = 0; i < 4; i++) {
        correctPattern[i] = (i + 1) * 90;  // 90, 180, 270, 360 degrees
        currentPattern[i] = 0;
        rotation[i] = 0.0f;
    }
}

void PatternPuzzle::Update(float deltaTime) {
    if (!isActive) return;

    // Smoothly rotate elements
    for (int i = 0; i < 4; i++) {
        if (rotation[i] < currentPattern[i]) {
            rotation[i] += deltaTime * 180.0f;
            if (rotation[i] > currentPattern[i]) {
                rotation[i] = currentPattern[i];
            }
        }
    }
}

void PatternPuzzle::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? WHITE : color;

    DrawCube(pos, 0.5f, 0.5f, 0.1f, renderColor);

    // Draw 4 rotating elements
    for (int i = 0; i < 4; i++) {
        float x = pos.x + (i % 2) * 0.15f - 0.075f;
        float y = pos.y + (i / 2) * 0.15f - 0.075f;

        rlPushMatrix();
        rlTranslatef(x, y, pos.z + 0.06f);
        rlRotatef(rotation[i], 0, 0, 1);
        DrawRectangle(-5, -5, 10, 20, ORANGE);
        rlPopMatrix();
    }
}

void PatternPuzzle::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive || isSolved) return;
    isActive_input = !isActive_input;
}

void PatternPuzzle::RotateElement(int idx) {
    if (!isActive_input || idx < 0 || idx >= 4) return;

    currentPattern[idx] = (currentPattern[idx] + 90) % 360;
    CheckPattern();
}

void PatternPuzzle::CheckPattern() {
    bool allCorrect = true;
    for (int i = 0; i < 4; i++) {
        if (currentPattern[i] != correctPattern[i]) {
            allCorrect = false;
            break;
        }
    }

    if (allCorrect) {
        isSolved = true;
        isActive_input = false;
    }
}
