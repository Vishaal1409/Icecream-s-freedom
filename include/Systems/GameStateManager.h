#pragma once

#include <string>

/**
 * GameStateManager - Manages game states (playing, paused, menu, won, etc.)
 *
 * Centralized state management for the game.
 */
enum class GameState {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    WON,
    GAME_OVER,
    SETTINGS
};

class GameStateManager {
private:
    GameState currentState;
    GameState previousState;
    float stateTimer;

public:
    GameStateManager();

    // State management
    void SetState(GameState newState);
    GameState GetState() const { return currentState; }
    GameState GetPreviousState() const { return previousState; }

    // Utility
    bool IsPlaying() const { return currentState == GameState::PLAYING; }
    bool IsPaused() const { return currentState == GameState::PAUSED; }
    bool IsInMenu() const { return currentState == GameState::MAIN_MENU; }
    bool HasWon() const { return currentState == GameState::WON; }

    void Update(float deltaTime);
    const char* GetStateString() const;
};
