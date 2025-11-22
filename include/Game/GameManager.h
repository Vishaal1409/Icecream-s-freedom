#pragma once

#include "raylib.h"
#include "Game/Player.h"
#include "Game/Room.h"
#include "Core/GameObject.h"
#include "Systems/InteractionSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/UIManager.h"
#include "Systems/GameStateManager.h"
#include "GameObjects/SimonSaysPuzzle.h"
#include "GameObjects/PatternPuzzle.h"
#include "GameObjects/LightSwitchPuzzle.h"
#include <vector>
#include <memory>
#include <ctime>

/**
 * GameManager Class - Demonstrates COMPOSITION and ORCHESTRATION
 *
 * The main game controller that COMPOSES multiple subsystems.
 * Shows "Favor composition over inheritance" principle.
 * This class HAS-A Player, HAS-A Room, HAS-A InteractionSystem, etc.
 */
class GameManager {
private:
    // COMPOSITION - GameManager HAS-A relationship with all these systems
    std::unique_ptr<Player> player;
    std::unique_ptr<Room> room;
    std::unique_ptr<CollisionSystem> collisionSystem;
    std::unique_ptr<InteractionSystem> interactionSystem;
    std::unique_ptr<GameStateManager> stateManager;
    UIManager& uiManager;  // Singleton reference, not owned

    // POLYMORPHISM - Store all game objects as base class pointers
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    // Game state
    bool isPaused;
    bool gameWon;
    bool isCursorLocked;  // Track cursor lock state
    float gameTime;  // Elapsed game time

public:
    GameManager();
    ~GameManager() = default;

    // Game loop methods
    void Initialize();
    void Update(float deltaTime);
    void Render();
    void HandleInput();

    // Game state
    bool IsGameWon() const { return gameWon; }
    bool IsPaused() const { return isPaused; }
    void SetPaused(bool paused) { isPaused = paused; }

    // Access to player (for interaction callbacks)
    Player& GetPlayer() { return *player; }

private:
    // ENCAPSULATION - Private initialization methods
    void InitializeSystems();
    void CreateGameObjects();
    void SetupLighting();

    // Game object creation helpers
    void CreateKeys();
    void CreateDoors();
    void CreateNotes();
    void CreatePuzzle();
    void CreatePuzzles();  // Create advanced puzzle types
    void CreateChest();

    // Interaction handling
    void HandleInteractionInput();
    void HandleCodeInput();

    // Check win condition
    void CheckWinCondition();

    // Cursor management
    void UpdateCursorState();
};
