#pragma once

#include <string>
#include <unordered_map>
#include <memory>

/**
 * AudioManager - Sound effects and music manager
 *
 * Provides a simple interface for playing sound effects and background music.
 * Note: Raylib audio system would require loading Sound structures.
 * This is a stub implementation with placeholder methods.
 */
class AudioManager {
private:
    bool soundEnabled;
    float masterVolume;

public:
    AudioManager();
    ~AudioManager() = default;

    // Enable/disable sound
    void SetEnabled(bool enabled) { soundEnabled = enabled; }
    bool IsEnabled() const { return soundEnabled; }

    // Volume control
    void SetMasterVolume(float volume);
    float GetMasterVolume() const { return masterVolume; }

    // Sound effect methods
    void PlaySFX(const std::string& sfxName, float volume = 1.0f);
    void PlayMusic(const std::string& musicName, float volume = 0.7f);
    void StopMusic();

    // Specific game sound effects
    void PlayKeyCollect() { PlaySFX("key_collect", 0.8f); }
    void PlayPuzzleSolve() { PlaySFX("puzzle_solve", 1.0f); }
    void PlayDoorUnlock() { PlaySFX("door_unlock", 0.9f); }
    void PlayWinSound() { PlaySFX("win", 1.0f); }
    void PlayErrorSound() { PlaySFX("error", 0.6f); }
};
