#include "GameObjects/LightSwitchPuzzle.h"
#include "Game/Player.h"

LightSwitchPuzzle::LightSwitchPuzzle(const std::string& name, Vector3 position)
    : GameObject(name, position, true)
    , isSolved(false) {

    color = YELLOW;

    // Setup pattern: switches 0,2,4 should be ON
    for (int i = 0; i < 6; i++) {
        switchStates[i] = false;
        correctSequence[i] = (i % 2 == 0);  // Alternate pattern
    }
}

void LightSwitchPuzzle::Update([[maybe_unused]] float deltaTime) {
    if (!isActive) return;
}

void LightSwitchPuzzle::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? WHITE : color;

    DrawCube(pos, 0.4f, 0.6f, 0.1f, renderColor);

    // Draw 6 switches in 2 rows of 3
    for (int i = 0; i < 6; i++) {
        float x = pos.x + (i % 3) * 0.12f - 0.12f;
        float y = pos.y + (i / 3) * 0.15f - 0.075f;

        Color switchColor = switchStates[i] ? GREEN : RED;
        DrawCube({x, y, pos.z + 0.06f}, 0.08f, 0.1f, 0.03f, switchColor);
    }
}

void LightSwitchPuzzle::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive || isSolved) return;
    // Interaction handled via switch toggles
}

void LightSwitchPuzzle::ToggleSwitch(int switchIdx) {
    if (switchIdx < 0 || switchIdx >= 6 || isSolved) return;

    switchStates[switchIdx] = !switchStates[switchIdx];
    CheckSolution();
}

void LightSwitchPuzzle::CheckSolution() {
    bool correct = true;
    for (int i = 0; i < 6; i++) {
        if (switchStates[i] != correctSequence[i]) {
            correct = false;
            break;
        }
    }

    if (correct) {
        isSolved = true;
    }
}
