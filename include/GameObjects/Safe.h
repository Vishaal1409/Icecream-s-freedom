#pragma once

#include "Core/GameObject.h"
#include <string>

/**
 * Safe Class - Interactive safe with combination lock
 *
 * A wall-mounted safe that requires a combination to open.
 * Contains a valuable item inside.
 */
class Safe : public GameObject {
private:
    // State
    bool isOpen;
    float doorRotation;
    bool isOpening;
    float openProgress;
    float openSpeed;

    // Combination
    std::string correctCode;
    std::string currentInput;

    // Item inside
    std::string containedItemID;

public:
    // Constructor
    Safe(const std::string& name, Vector3 position, const std::string& code = "5432");

    // POLYMORPHISM
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // Getters
    bool IsOpen() const { return isOpen; }
    const std::string& GetContainedItemID() const { return containedItemID; }

    // Code handling
    void AddDigit(char digit);
    void ClearInput();
    void SubmitCode();

private:
    void CheckCode();
    void OpenSafe();
    void UpdateAnimation(float deltaTime);
};
