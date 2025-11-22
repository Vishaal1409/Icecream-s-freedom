#include "Systems/EffectsManager.h"

EffectsManager::EffectsManager()
    : shakeIntensity(0.0f)
    , shakeTimer(0.0f)
    , shakeDuration(0.0f)
    , currentTint(WHITE)
    , tintTimer(0.0f)
    , tintDuration(0.0f) {
}

void EffectsManager::StartShake(float intensity, float duration) {
    shakeIntensity = intensity;
    shakeDuration = duration;
    shakeTimer = 0.0f;
}

void EffectsManager::Update(float deltaTime) {
    // Update screen shake
    if (shakeTimer < shakeDuration) {
        shakeTimer += deltaTime;
    } else {
        shakeIntensity = 0.0f;
    }

    // Update color tint
    if (tintTimer < tintDuration) {
        tintTimer += deltaTime;
        // Fade out tint over time
        float progress = tintTimer / tintDuration;
        currentTint.a = static_cast<unsigned char>(255 * (1.0f - progress));
    } else {
        currentTint = WHITE;
    }
}

Vector2 EffectsManager::GetShakeOffset() {
    if (shakeIntensity <= 0.0f) {
        return Vector2{0, 0};
    }

    // Random shake offset
    float offsetX = (GetRandomValue(-1, 1) * shakeIntensity);
    float offsetY = (GetRandomValue(-1, 1) * shakeIntensity);

    return Vector2{offsetX, offsetY};
}

void EffectsManager::StartTint(Color color, float duration) {
    currentTint = color;
    tintDuration = duration;
    tintTimer = 0.0f;
}
