#pragma once

#include "Core/GameObject.h"

/**
 * LightSwitchPuzzle - Activate lights in correct sequence
 */
class LightSwitchPuzzle : public GameObject {
private:
    bool switchStates[6];
    bool correctSequence[6];
    bool isSolved;

public:
    LightSwitchPuzzle(const std::string& name, Vector3 position);

    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    bool IsSolved() const { return isSolved; }
    void ToggleSwitch(int switchIdx);

private:
    void CheckSolution();
};
