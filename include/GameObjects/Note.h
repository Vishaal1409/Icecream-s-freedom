#pragma once

#include "Core/GameObject.h"
#include <string>

/**
 * Note Class - Demonstrates INHERITANCE and POLYMORPHISM
 *
 * Readable notes that provide clues for puzzles.
 * Different interaction behavior compared to Keys and Doors.
 */
class Note : public GameObject {
private:
    // ENCAPSULATION - Private member variables
    std::string noteText;
    bool hasBeenRead;

public:
    // Constructor
    Note(const std::string& name, Vector3 position, const std::string& text);

    // POLYMORPHISM - Override base class methods with Note-specific behavior
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // ENCAPSULATION - Getters
    const std::string& GetNoteText() const { return noteText; }
    bool HasBeenRead() const { return hasBeenRead; }
};
