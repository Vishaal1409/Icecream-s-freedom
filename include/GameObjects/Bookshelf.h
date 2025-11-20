#pragma once

#include "Core/GameObject.h"

/**
 * Bookshelf Class - Interactive furniture with books and clues
 *
 * A bookshelf containing books, some of which hide clues/notes.
 */
class Bookshelf : public GameObject {
private:
    bool hasSecret;
    bool secretRevealed;

public:
    // Constructor
    Bookshelf(const std::string& name, Vector3 position, bool containsSecret = true);

    // POLYMORPHISM
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    bool HasSecret() const { return hasSecret && !secretRevealed; }
    void RevealSecret() { secretRevealed = true; }
};
