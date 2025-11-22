#include "Systems/GameStateManager.h"

GameStateManager::GameStateManager()
    : currentState(GameState::MAIN_MENU)
    , previousState(GameState::MAIN_MENU)
    , stateTimer(0.0f) {
}

void GameStateManager::SetState(GameState newState) {
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;
        stateTimer = 0.0f;
    }
}

void GameStateManager::Update(float deltaTime) {
    stateTimer += deltaTime;
}

const char* GameStateManager::GetStateString() const {
    switch (currentState) {
        case GameState::MAIN_MENU:
            return "MAIN_MENU";
        case GameState::PLAYING:
            return "PLAYING";
        case GameState::PAUSED:
            return "PAUSED";
        case GameState::WON:
            return "WON";
        case GameState::GAME_OVER:
            return "GAME_OVER";
        case GameState::SETTINGS:
            return "SETTINGS";
        default:
            return "UNKNOWN";
    }
}
