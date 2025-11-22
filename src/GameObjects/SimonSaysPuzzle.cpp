#include "GameObjects/SimonSaysPuzzle.h"
#include "Game/Player.h"
#include <cstdlib>

SimonSaysPuzzle::SimonSaysPuzzle(const std::string& name, Vector3 position)
    : GameObject(name, position, true)
    , currentLevel(0)
    , isActive_input(false)
    , isSolved(false)
    , feedbackTimer(0.0f)
    , showingFeedback(false) {

    color = PURPLE;
    // Initialize with first color
    sequence.push_back(rand() % 4);
}

void SimonSaysPuzzle::Update(float deltaTime) {
    if (!isActive) return;

    if (showingFeedback) {
        feedbackTimer += deltaTime;
        if (feedbackTimer > 1.0f) {
            showingFeedback = false;
        }
    }
}

void SimonSaysPuzzle::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? WHITE : color;

    // Draw main puzzle panel
    DrawCube(pos, 0.4f, 0.5f, 0.1f, renderColor);

    // Draw 4 color buttons
    Color buttons[4] = {RED, YELLOW, BLUE, GREEN};
    for (int i = 0; i < 4; i++) {
        float xOffset = (i % 2) * 0.15f - 0.075f;
        float yOffset = (i / 2) * 0.15f - 0.075f;
        Vector3 buttonPos = {pos.x + xOffset, pos.y + yOffset, pos.z + 0.06f};

        DrawCube(buttonPos, 0.1f, 0.1f, 0.05f, buttons[i]);
    }

    // Show level
    DrawText(TextFormat("L:%d", currentLevel + 1), (int)pos.x - 20, (int)pos.y - 100, 10, WHITE);
}

void SimonSaysPuzzle::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive || isSolved) return;

    isActive_input = !isActive_input;
    if (isActive_input) {
        PlaySequence();
    }
}

void SimonSaysPuzzle::AddColor(int colorIdx) {
    if (!isActive_input || isSolved) return;

    playerInput.push_back(colorIdx);
    CheckInput();
}

void SimonSaysPuzzle::PlaySequence() {
    // In a real implementation, would play sounds/animations
    // For now, just mark that sequence started
}

void SimonSaysPuzzle::CheckInput() {
    // Check if player input matches sequence so far
    for (size_t i = 0; i < playerInput.size(); i++) {
        if (playerInput[i] != sequence[i]) {
            // Wrong! Reset
            Reset();
            return;
        }
    }

    // If player completed the sequence
    if (playerInput.size() == sequence.size()) {
        NextLevel();
    }
}

void SimonSaysPuzzle::NextLevel() {
    currentLevel++;
    playerInput.clear();

    if (currentLevel >= 4) {
        // Puzzle solved!
        isSolved = true;
        isActive_input = false;
    } else {
        // Add next color to sequence
        sequence.push_back(rand() % 4);
    }
}

void SimonSaysPuzzle::Reset() {
    playerInput.clear();
    showingFeedback = true;
    feedbackTimer = 0.0f;
}
