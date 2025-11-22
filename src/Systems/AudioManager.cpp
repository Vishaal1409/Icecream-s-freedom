#include "Systems/AudioManager.h"

AudioManager::AudioManager()
    : soundEnabled(true)
    , masterVolume(1.0f) {
}

void AudioManager::SetMasterVolume(float volume) {
    // Clamp volume between 0.0 and 1.0
    if (volume < 0.0f) {
        masterVolume = 0.0f;
    } else if (volume > 1.0f) {
        masterVolume = 1.0f;
    } else {
        masterVolume = volume;
    }
}

void AudioManager::PlaySFX(const std::string& sfxName, float volume) {
    if (!soundEnabled) return;

    // Adjust volume by master volume
    float finalVolume = volume * masterVolume;

    // In a full implementation, this would load and play a Sound from raylib
    // For now, just a placeholder that logs which sound would play
    // Example sounds: "key_collect", "puzzle_solve", "door_unlock", "win", "error"

    // Could add real audio support here:
    // Sound sound = LoadSound("resources/sounds/" + sfxName + ".wav");
    // SetSoundVolume(sound, finalVolume);
    // PlaySound(sound);
    // UnloadSound(sound);
}

void AudioManager::PlayMusic(const std::string& musicName, float volume) {
    if (!soundEnabled) return;

    // Adjust volume by master volume
    float finalVolume = volume * masterVolume;

    // In a full implementation, this would load and play Music from raylib
    // For now, just a placeholder

    // Could add real audio support here:
    // Music music = LoadMusicStream("resources/music/" + musicName + ".ogg");
    // SetMusicVolume(music, finalVolume);
    // PlayMusicStream(music);
}

void AudioManager::StopMusic() {
    // Would stop currently playing music stream
}
