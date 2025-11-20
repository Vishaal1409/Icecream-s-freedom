#pragma once

#include "Core/GameObject.h"
#include <string>
#include <functional>

/**
 * Puzzle Class - Demonstrates INHERITANCE, POLYMORPHISM, and CALLBACKS
 *
 * A code lock puzzle that requires a 4-digit code to solve.
 * Shows complex state management and callback patterns.
 */
class Puzzle : public GameObject {
private:
    // ENCAPSULATION - Private state management
    std::string correctCode;
    std::string currentInput;
    bool isSolved;
    bool isActive_input;  // Is the puzzle UI currently active
    float displayTimer;   // For feedback animation
    bool showingFeedback;
    bool lastAttemptCorrect;

    // Callback function pointer (optional feature for advanced students)
    std::function<void()> onSolveCallback;

public:
    // Constructor
    Puzzle(const std::string& name, Vector3 position, const std::string& code);

    // POLYMORPHISM - Override base class methods
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // ENCAPSULATION - Getters
    bool IsSolved() const { return isSolved; }
    bool IsInputActive() const { return isActive_input; }
    const std::string& GetCurrentInput() const { return currentInput; }

    // Set callback for when puzzle is solved
    void SetOnSolveCallback(std::function<void()> callback) { onSolveCallback = callback; }

    // Input handling
    void AddDigit(char digit);
    void ClearInput();
    void SubmitCode();

private:
    // ENCAPSULATION - Private helper methods
    void CheckCode();
    void Solve();
    void ShowFeedback(bool correct);
};
