/**
 * 3D Escape Room - Main Entry Point
 *
 * A C++ game demonstrating Object-Oriented Programming principles:
 * - INHERITANCE: GameObject base class with derived types
 * - ENCAPSULATION: Private members with public interfaces
 * - POLYMORPHISM: Virtual functions with different implementations
 * - ABSTRACTION: High-level interfaces hiding complexity
 * - COMPOSITION: GameManager composes multiple subsystems
 *
 * Built with Raylib 5.0 and C++17
 */

#include "raylib.h"
#include "GameManager.h"
#include <memory>

// Window configuration
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const char* WINDOW_TITLE = "3D Escape Room - OOP Project";
const int TARGET_FPS = 60;

int main() {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    // Disable ESC key closing window (we handle it manually)
    SetExitKey(KEY_NULL);

    // Don't lock cursor immediately - let GameManager control it based on game state
    EnableCursor();

    // COMPOSITION - Create game manager which composes all subsystems
    std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();

    // Main game loop
    while (!WindowShouldClose()) {
        // Calculate delta time
        float deltaTime = GetFrameTime();

        // Update game
        gameManager->Update(deltaTime);

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        // POLYMORPHISM in action - GameManager calls Render on all objects
        // through base class pointers, each object renders differently
        gameManager->Render();

        // Display FPS
        DrawFPS(10, SCREEN_HEIGHT - 30);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}
