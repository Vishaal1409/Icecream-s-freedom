#pragma once

#include "raylib.h"
#include <vector>
#include <string>

/**
 * SaveGameManager - Save and load game state
 *
 * Provides functionality to save and load game progress.
 * Stores player position, inventory, puzzle states, and elapsed time.
 */
struct GameSaveData {
    float playerX, playerY, playerZ;
    float gameTime;
    std::vector<std::string> inventory;
    bool puzzleSolved;
    bool chestOpened;
    bool doorUnlocked;
};

class SaveGameManager {
private:
    std::string savePath;

public:
    SaveGameManager();

    // Save and load
    bool SaveGame(const GameSaveData& data, const std::string& filename = "savegame.dat");
    bool LoadGame(GameSaveData& data, const std::string& filename = "savegame.dat");

    // Utility
    bool SaveGameExists(const std::string& filename = "savegame.dat");
    void DeleteSaveGame(const std::string& filename = "savegame.dat");
};
