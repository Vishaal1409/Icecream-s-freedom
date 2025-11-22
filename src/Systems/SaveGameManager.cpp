#include "Systems/SaveGameManager.h"
#include <fstream>
#include <sstream>
#include <cstdio>

SaveGameManager::SaveGameManager()
    : savePath("saves/") {
    // Create saves directory if it doesn't exist
    // In a full implementation, would use platform-specific directory creation
}

bool SaveGameManager::SaveGame(const GameSaveData& data, const std::string& filename) {
    std::string fullPath = savePath + filename;

    // Open file for binary writing
    std::ofstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Write player position
    file.write(reinterpret_cast<const char*>(&data.playerX), sizeof(float));
    file.write(reinterpret_cast<const char*>(&data.playerY), sizeof(float));
    file.write(reinterpret_cast<const char*>(&data.playerZ), sizeof(float));

    // Write game time
    file.write(reinterpret_cast<const char*>(&data.gameTime), sizeof(float));

    // Write inventory size and items
    size_t inventorySize = data.inventory.size();
    file.write(reinterpret_cast<const char*>(&inventorySize), sizeof(size_t));
    for (const auto& item : data.inventory) {
        size_t itemLen = item.length();
        file.write(reinterpret_cast<const char*>(&itemLen), sizeof(size_t));
        file.write(item.c_str(), itemLen);
    }

    // Write puzzle states
    file.write(reinterpret_cast<const char*>(&data.puzzleSolved), sizeof(bool));
    file.write(reinterpret_cast<const char*>(&data.chestOpened), sizeof(bool));
    file.write(reinterpret_cast<const char*>(&data.doorUnlocked), sizeof(bool));

    file.close();
    return true;
}

bool SaveGameManager::LoadGame(GameSaveData& data, const std::string& filename) {
    std::string fullPath = savePath + filename;

    // Open file for binary reading
    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Read player position
    file.read(reinterpret_cast<char*>(&data.playerX), sizeof(float));
    file.read(reinterpret_cast<char*>(&data.playerY), sizeof(float));
    file.read(reinterpret_cast<char*>(&data.playerZ), sizeof(float));

    // Read game time
    file.read(reinterpret_cast<char*>(&data.gameTime), sizeof(float));

    // Read inventory size and items
    size_t inventorySize = 0;
    file.read(reinterpret_cast<char*>(&inventorySize), sizeof(size_t));
    data.inventory.clear();
    for (size_t i = 0; i < inventorySize; i++) {
        size_t itemLen = 0;
        file.read(reinterpret_cast<char*>(&itemLen), sizeof(size_t));
        char buffer[256];
        file.read(buffer, itemLen);
        data.inventory.push_back(std::string(buffer, itemLen));
    }

    // Read puzzle states
    file.read(reinterpret_cast<char*>(&data.puzzleSolved), sizeof(bool));
    file.read(reinterpret_cast<char*>(&data.chestOpened), sizeof(bool));
    file.read(reinterpret_cast<char*>(&data.doorUnlocked), sizeof(bool));

    file.close();
    return true;
}

bool SaveGameManager::SaveGameExists(const std::string& filename) {
    std::string fullPath = savePath + filename;
    std::ifstream file(fullPath);
    return file.good();
}

void SaveGameManager::DeleteSaveGame(const std::string& filename) {
    std::string fullPath = savePath + filename;
    std::remove(fullPath.c_str());
}
