#pragma once

#include "Core/GameObject.h"

/**
 * PatternPuzzle - Match the pattern by rotating shapes
 */
class PatternPuzzle : public GameObject {
private:
    float rotation[4];  // 4 rotating elements
    bool isActive_input;
    bool isSolved;
    int correctPattern[4];
    int currentPattern[4];

public:
    PatternPuzzle(const std::string& name, Vector3 position);

    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    bool IsSolved() const { return isSolved; }
    void RotateElement(int idx);
    void CheckPattern();
};
