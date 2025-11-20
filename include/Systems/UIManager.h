#pragma once

#include "raylib.h"
#include "Systems/Inventory.h"
#include <string>
#include <vector>

/**
 * UIManager Class - Demonstrates SINGLETON PATTERN and ENCAPSULATION
 *
 * Manages all UI rendering and display.
 * Uses Singleton pattern to ensure only one UI manager exists.
 */
class UIManager {
private:
    // SINGLETON - Private constructor
    UIManager();

    // ENCAPSULATION - Private state
    bool showInstructions;
    bool showNoteViewer;
    bool showCodeInput;
    bool showWinScreen;
    bool showPauseMenu;
    std::string currentNoteText;
    std::string currentMessage;
    float messageTimer;
    std::string codeInput;
    float gameTime;  // Elapsed game time
    std::vector<std::string> hints;
    int currentHintIndex;

public:
    // SINGLETON - Static access method (returns reference to avoid memory leaks)
    static UIManager& GetInstance();

    // Delete copy constructor and assignment operator (Singleton pattern)
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    // UI Display Methods
    void RenderUI(const Inventory& inventory, bool hasTarget);
    void ShowMessage(const std::string& message, float duration = 3.0f);
    void ShowNote(const std::string& text);
    void HideNote();
    void ShowCodeInputUI();
    void HideCodeInputUI();
    void ShowWin();

    // UI State
    void Update(float deltaTime);
    bool IsAnyUIActive() const;
    bool IsCodeInputActive() const { return showCodeInput; }
    const std::string& GetCodeInput() const { return codeInput; }
    void AddCodeDigit(char digit);
    void ClearCodeInput();

    // Menu and timer
    void TogglePauseMenu() { showPauseMenu = !showPauseMenu; }
    void ClosePauseMenu() { showPauseMenu = false; }
    bool IsPauseMenuActive() const { return showPauseMenu; }
    void SetGameTime(float time) { gameTime = time; }

    // Hints system
    void InitializeHints();
    void ShowNextHint();
    const std::string& GetCurrentHint() const;
    bool HasMoreHints() const { return currentHintIndex < hints.size() - 1; }

private:
    // ENCAPSULATION - Private rendering methods
    void RenderCrosshair();
    void RenderInventory(const Inventory& inventory);
    void RenderInteractionPrompt();
    void RenderMessage();
    void RenderNoteViewer();
    void RenderCodeInputUI();
    void RenderWinScreen();
    void RenderInstructions();
    void RenderTimer();
    void RenderHints();
    void RenderPauseMenu();
};
