#include "GameObjects/Puzzle.h"
#include "Game/Player.h"

Puzzle::Puzzle(const std::string& name, Vector3 position, const std::string& code)
    : GameObject(name, position, true)
    , correctCode(code)
    , currentInput("")
    , isSolved(false)
    , isActive_input(false)
    , displayTimer(0.0f)
    , showingFeedback(false)
    , lastAttemptCorrect(false)
    , onSolveCallback(nullptr) {

    color = DARKGRAY;
}

void Puzzle::Update(float deltaTime) {
    if (!isActive) return;

    // Update feedback timer
    if (showingFeedback) {
        displayTimer += deltaTime;
        if (displayTimer >= 2.0f) {  // Show feedback for 2 seconds
            showingFeedback = false;
            displayTimer = 0.0f;
        }
    }
}

void Puzzle::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? LIGHTGRAY : color;

    // Draw main panel
    DrawCube(pos, 0.6f, 0.8f, 0.1f, renderColor);

    // Draw display screen
    Color screenColor = isSolved ? GREEN : (showingFeedback ? (lastAttemptCorrect ? GREEN : RED) : DARKGREEN);
    Vector3 screenPos = {pos.x, pos.y + 0.25f, pos.z + 0.08f};
    DrawCube(screenPos, 0.5f, 0.15f, 0.05f, screenColor);

    // Draw number pad buttons (3x4 grid)
    float buttonSize = 0.12f;
    float spacing = 0.15f;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            Vector3 buttonPos = {
                pos.x + (col - 1) * spacing,
                pos.y + 0.05f - row * spacing,
                pos.z + 0.08f
            };
            DrawCube(buttonPos, buttonSize, buttonSize, 0.04f, GRAY);
        }
    }
}

void Puzzle::OnInteract(Player* player) {
    if (!isActive || isSolved) return;

    // POLYMORPHISM - Puzzle-specific interaction
    // Activate puzzle input mode
    isActive_input = true;
}

void Puzzle::AddDigit(char digit) {
    if (currentInput.length() < 4 && !isSolved) {
        currentInput += digit;
    }
}

void Puzzle::ClearInput() {
    currentInput.clear();
}

void Puzzle::SubmitCode() {
    if (currentInput.length() == 4) {
        CheckCode();
    }
}

void Puzzle::CheckCode() {
    if (currentInput == correctCode) {
        Solve();
        ShowFeedback(true);
    } else {
        ShowFeedback(false);
        currentInput.clear();
    }
}

void Puzzle::Solve() {
    isSolved = true;
    isActive_input = false;

    // Call the callback if it exists
    if (onSolveCallback) {
        onSolveCallback();
    }
}

void Puzzle::ShowFeedback(bool correct) {
    showingFeedback = true;
    lastAttemptCorrect = correct;
    displayTimer = 0.0f;
}
