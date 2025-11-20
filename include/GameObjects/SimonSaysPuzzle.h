#pragma once

#include "Core/GameObject.h"
#include <vector>

/**
 * SimonSaysPuzzle - Memory sequence puzzle
 *
 * Player must repeat an increasingly long sequence of colors.
 * Classic Simon Says game mechanics.
 */
class SimonSaysPuzzle : public GameObject {
private:
    std::vector<int> sequence;
    std::vector<int> playerInput;
    int currentLevel;
    bool isActive_input;
    bool isSolved;
    float feedbackTimer;
    bool showingFeedback;

public:
    SimonSaysPuzzle(const std::string& name, Vector3 position);

    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    bool IsSolved() const { return isSolved; }
    void AddColor(int colorIdx);
    void PlaySequence();

private:
    void NextLevel();
    void CheckInput();
    void Reset();
};
