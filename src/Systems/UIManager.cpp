#include "Systems/UIManager.h"
#include <algorithm>

UIManager::UIManager()
    : showInstructions(true)
    , showNoteViewer(false)
    , showCodeInput(false)
    , showWinScreen(false)
    , showPauseMenu(false)
    , currentNoteText("")
    , currentMessage("")
    , messageTimer(0.0f)
    , codeInput("")
    , gameTime(0.0f)
    , currentHintIndex(0) {
    InitializeHints();
}

UIManager& UIManager::GetInstance() {
    static UIManager instance;  // Meyer's Singleton - created once, thread-safe, no memory leak
    return instance;
}

void UIManager::Update(float deltaTime) {
    // Update message timer
    if (!currentMessage.empty()) {
        messageTimer -= deltaTime;
        if (messageTimer <= 0.0f) {
            currentMessage.clear();
        }
    }
}

void UIManager::RenderUI(const Inventory& inventory, bool hasTarget) {
    // Render instructions if showing
    if (showInstructions) {
        RenderInstructions();
        return;  // Don't show other UI while instructions are up
    }

    // Render pause menu on top if active
    if (showPauseMenu) {
        RenderPauseMenu();
        return;  // Don't show other game UI while paused
    }

    // Render normal game UI
    RenderCrosshair();
    RenderInventory(inventory);
    RenderTimer();
    RenderHints();

    if (hasTarget) {
        RenderInteractionPrompt();
    }

    if (!currentMessage.empty()) {
        RenderMessage();
    }

    // Render modal UIs
    if (showNoteViewer) {
        RenderNoteViewer();
    }

    if (showCodeInput) {
        RenderCodeInputUI();
    }

    if (showWinScreen) {
        RenderWinScreen();
    }
}

void UIManager::ShowMessage(const std::string& message, float duration) {
    currentMessage = message;
    messageTimer = duration;
}

void UIManager::ShowNote(const std::string& text) {
    currentNoteText = text;
    showNoteViewer = true;
}

void UIManager::HideNote() {
    showNoteViewer = false;
    currentNoteText.clear();
}

void UIManager::ShowCodeInputUI() {
    showCodeInput = true;
    codeInput.clear();
}

void UIManager::HideCodeInputUI() {
    showCodeInput = false;
    codeInput.clear();
}

void UIManager::ShowWin() {
    showWinScreen = true;
}

bool UIManager::IsAnyUIActive() const {
    return showInstructions || showNoteViewer || showCodeInput || showWinScreen || showPauseMenu;
}

void UIManager::AddCodeDigit(char digit) {
    if (codeInput.length() < 4 && digit >= '0' && digit <= '9') {
        codeInput += digit;
    }
}

void UIManager::ClearCodeInput() {
    codeInput.clear();
}

// Private rendering methods
void UIManager::RenderCrosshair() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
    int size = 10;

    DrawLine(centerX - size, centerY, centerX + size, centerY, WHITE);
    DrawLine(centerX, centerY - size, centerX, centerY + size, WHITE);
}

void UIManager::RenderInventory(const Inventory& inventory) {
    int x = 20;
    int y = 20;
    int width = 200;
    int lineHeight = 25;

    DrawRectangle(x, y, width, 150, Color{0, 0, 0, 180});
    DrawRectangleLines(x, y, width, 150, GRAY);

    DrawText("INVENTORY", x + 10, y + 10, 20, GOLD);

    const auto& items = inventory.GetAllItems();
    if (items.empty()) {
        DrawText("Empty", x + 10, y + 40, 16, DARKGRAY);
    } else {
        int itemY = y + 40;
        for (const auto& item : items) {
            std::string displayText = "• " + item + " Key";
            DrawText(displayText.c_str(), x + 10, itemY, 16, WHITE);
            itemY += lineHeight;
        }
    }
}

void UIManager::RenderInteractionPrompt() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char* text = "Press E to interact";

    int textWidth = MeasureText(text, 18);
    int x = (screenWidth - textWidth) / 2;
    int y = screenHeight - 120;

    DrawRectangle(x - 15, y - 5, textWidth + 30, 30, Color{0, 0, 0, 180});
    DrawRectangleLines(x - 15, y - 5, textWidth + 30, 30, GOLD);
    DrawText(text, x, y, 18, WHITE);
}

void UIManager::RenderMessage() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int textWidth = MeasureText(currentMessage.c_str(), 20);
    int x = (screenWidth - textWidth) / 2;
    int y = screenHeight - 180;

    DrawRectangle(x - 20, y - 10, textWidth + 40, 40, Color{0, 0, 0, 200});
    DrawRectangleLines(x - 20, y - 10, textWidth + 40, 40, SKYBLUE);
    DrawText(currentMessage.c_str(), x, y, 20, WHITE);
}

void UIManager::RenderNoteViewer() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int boxWidth = 600;
    int boxHeight = 400;
    int x = (screenWidth - boxWidth) / 2;
    int y = (screenHeight - boxHeight) / 2;

    // Background overlay
    DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 150});

    // Note panel
    DrawRectangle(x, y, boxWidth, boxHeight, Color{245, 245, 220, 255});
    DrawRectangleLines(x, y, boxWidth, boxHeight, DARKBROWN);

    // Title
    DrawText("NOTE", x + 20, y + 20, 24, DARKBROWN);
    DrawLine(x + 20, y + 50, x + boxWidth - 20, y + 50, DARKBROWN);

    // Content (word-wrapped manually for simplicity)
    DrawText(currentNoteText.c_str(), x + 20, y + 70, 18, BLACK);

    // Close instruction
    DrawText("Press ESC to close", x + boxWidth - 180, y + boxHeight - 40, 16, DARKGRAY);
}

void UIManager::RenderCodeInputUI() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int boxWidth = 400;
    int boxHeight = 500;
    int x = (screenWidth - boxWidth) / 2;
    int y = (screenHeight - boxHeight) / 2;

    // Background overlay
    DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 150});

    // Panel
    DrawRectangle(x, y, boxWidth, boxHeight, Color{40, 40, 40, 255});
    DrawRectangleLines(x, y, boxWidth, boxHeight, GREEN);

    // Title
    DrawText("ENTER CODE", x + (boxWidth - MeasureText("ENTER CODE", 24)) / 2, y + 20, 24, GREEN);

    // Display
    std::string displayText = codeInput;
    while (displayText.length() < 4) {
        displayText += "-";
    }

    int displayY = y + 80;
    DrawRectangle(x + 50, displayY, boxWidth - 100, 60, BLACK);
    DrawRectangleLines(x + 50, displayY, boxWidth - 100, 60, GREEN);
    DrawText(displayText.c_str(), x + 120, displayY + 15, 32, GREEN);

    // Number pad (3x4 grid)
    int buttonSize = 80;
    int spacing = 20;
    int startX = x + (boxWidth - (3 * buttonSize + 2 * spacing)) / 2;
    int startY = displayY + 100;

    const char* buttons[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "CLR", "0", "OK"};

    for (int i = 0; i < 12; i++) {
        int col = i % 3;
        int row = i / 3;
        int bx = startX + col * (buttonSize + spacing);
        int by = startY + row * (buttonSize + spacing);

        Color buttonColor = DARKGRAY;
        if (i == 9) buttonColor = RED;      // CLR
        if (i == 11) buttonColor = GREEN;   // OK

        DrawRectangle(bx, by, buttonSize, buttonSize, buttonColor);
        DrawRectangleLines(bx, by, buttonSize, buttonSize, LIGHTGRAY);

        int textWidth = MeasureText(buttons[i], 20);
        DrawText(buttons[i], bx + (buttonSize - textWidth) / 2, by + 30, 20, WHITE);
    }

    // Instructions
    DrawText("Use number keys or ESC to cancel", x + 60, y + boxHeight - 40, 14, LIGHTGRAY);
}

void UIManager::RenderWinScreen() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Background
    DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 230});

    // Title
    const char* title = "CONGRATULATIONS!";
    int titleWidth = MeasureText(title, 60);
    DrawText(title, (screenWidth - titleWidth) / 2, screenHeight / 2 - 100, 60, GOLD);

    // Subtitle
    const char* subtitle = "You Escaped!";
    int subtitleWidth = MeasureText(subtitle, 40);
    DrawText(subtitle, (screenWidth - subtitleWidth) / 2, screenHeight / 2 - 20, 40, GREEN);

    // Instructions
    const char* instructions = "Press ESC to exit";
    int instWidth = MeasureText(instructions, 20);
    DrawText(instructions, (screenWidth - instWidth) / 2, screenHeight / 2 + 60, 20, WHITE);
}

void UIManager::RenderInstructions() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int boxWidth = 700;
    int boxHeight = 550;
    int x = (screenWidth - boxWidth) / 2;
    int y = (screenHeight - boxHeight) / 2;

    // Background
    DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 200});

    // Panel
    DrawRectangle(x, y, boxWidth, boxHeight, Color{30, 30, 40, 255});
    DrawRectangleLines(x, y, boxWidth, boxHeight, GOLD);

    // Title
    DrawText("3D ESCAPE ROOM", x + (boxWidth - MeasureText("3D ESCAPE ROOM", 48)) / 2, y + 30, 48, GOLD);

    int textY = y + 110;
    int lineHeight = 35;

    // Controls
    DrawText("CONTROLS:", x + 50, textY, 24, SKYBLUE);
    textY += lineHeight + 10;

    DrawText("WASD - Move", x + 70, textY, 20, WHITE);
    textY += lineHeight;
    DrawText("Mouse - Look around", x + 70, textY, 20, WHITE);
    textY += lineHeight;
    DrawText("E - Interact with objects", x + 70, textY, 20, WHITE);
    textY += lineHeight;
    DrawText("ESC - Close menus / Quit", x + 70, textY, 20, WHITE);
    textY += lineHeight + 20;

    // Objectives
    DrawText("OBJECTIVES:", x + 50, textY, 24, SKYBLUE);
    textY += lineHeight + 10;

    DrawText("1. Explore and find keys", x + 70, textY, 18, WHITE);
    textY += lineHeight - 5;
    DrawText("2. Read notes for clues", x + 70, textY, 18, WHITE);
    textY += lineHeight - 5;
    DrawText("3. Solve the code puzzle (hint: 1842)", x + 70, textY, 18, WHITE);
    textY += lineHeight - 5;
    DrawText("4. Open the chest with blue key", x + 70, textY, 18, WHITE);
    textY += lineHeight - 5;
    DrawText("5. Get gold key and escape!", x + 70, textY, 18, WHITE);
    textY += lineHeight + 20;

    // Start instruction
    DrawText("Click to start and lock mouse", x + (boxWidth - MeasureText("Click to start and lock mouse", 22)) / 2, textY + 20, 22, GREEN);

    showInstructions = false;  // Hide after first render
}

void UIManager::InitializeHints() {
    hints.clear();
    hints.push_back("Press E to interact with objects");
    hints.push_back("Check notes for clues about the code");
    hints.push_back("The year 1842 might be important...");
    hints.push_back("Look for keys in different locations");
    hints.push_back("Puzzles require memory and pattern matching");
    hints.push_back("The exit is locked - you need the gold key!");
    currentHintIndex = 0;
}

void UIManager::ShowNextHint() {
    if (HasMoreHints()) {
        currentHintIndex++;
        ShowMessage("HINT: " + hints[currentHintIndex], 5.0f);
    }
}

const std::string& UIManager::GetCurrentHint() const {
    if (currentHintIndex < hints.size()) {
        return hints[currentHintIndex];
    }
    static std::string empty = "";
    return empty;
}

void UIManager::RenderTimer() {
    int screenWidth = GetScreenWidth();
    int minutes = static_cast<int>(gameTime) / 60;
    int seconds = static_cast<int>(gameTime) % 60;

    char timeStr[20];
    snprintf(timeStr, sizeof(timeStr), "TIME: %02d:%02d", minutes, seconds);

    // Render in top-right corner
    int textWidth = MeasureText(timeStr, 20);
    int x = screenWidth - textWidth - 30;
    int y = 20;

    DrawText(timeStr, x, y, 20, YELLOW);
}

void UIManager::RenderHints() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* hintText = "Press H for hint (or check notes for clues)";
    int textWidth = MeasureText(hintText, 16);
    int x = (screenWidth - textWidth) / 2;
    int y = screenHeight - 280;

    DrawText(hintText, x, y, 16, LIGHTGRAY);
}

void UIManager::RenderPauseMenu() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Background overlay
    DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 200});

    // Panel
    int boxWidth = 400;
    int boxHeight = 300;
    int x = (screenWidth - boxWidth) / 2;
    int y = (screenHeight - boxHeight) / 2;

    DrawRectangle(x, y, boxWidth, boxHeight, Color{30, 30, 40, 255});
    DrawRectangleLines(x, y, boxWidth, boxHeight, SKYBLUE);

    // Title
    const char* title = "PAUSED";
    int titleWidth = MeasureText(title, 48);
    DrawText(title, x + (boxWidth - titleWidth) / 2, y + 40, 48, SKYBLUE);

    // Options
    int textY = y + 130;
    DrawText("Press P to resume", x + 50, textY, 20, WHITE);
    textY += 50;
    DrawText("Press ESC to quit", x + 50, textY, 20, WHITE);
}
