#pragma once

#include "raylib.h"

/**
 * EffectsManager - Visual effects system
 *
 * Handles screen shake, color tints, and other visual feedback.
 */
class EffectsManager {
private:
    // Screen shake
    float shakeIntensity;
    float shakeTimer;
    float shakeDuration;

    // Color tint
    Color currentTint;
    float tintTimer;
    float tintDuration;

public:
    EffectsManager();

    // Screen shake effect
    void StartShake(float intensity, float duration);
    void Update(float deltaTime);

    // Apply effects
    Vector2 GetShakeOffset();
    Color GetTintColor() const { return currentTint; }

    // Color tint effects
    void StartTint(Color color, float duration);
};
