#include "GameObjects/Note.h"
#include "Game/Player.h"

Note::Note(const std::string& name, Vector3 position, const std::string& text)
    : GameObject(name, position, true)
    , noteText(text)
    , hasBeenRead(false) {

    color = BEIGE;
}

void Note::Update(float deltaTime) {
    // Notes are static, no animation needed
    // But we maintain the interface (POLYMORPHISM)
}

void Note::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? YELLOW : color;

    // Draw paper sheet
    DrawCube(pos, 0.3f, 0.4f, 0.01f, renderColor);

    // Draw decorative lines (representing text)
    for (int i = 0; i < 5; i++) {
        Vector3 linePos = {pos.x, pos.y + 0.15f - i * 0.06f, pos.z + 0.01f};
        DrawCube(linePos, 0.2f, 0.02f, 0.002f, DARKGRAY);
    }
}

void Note::OnInteract(Player* player) {
    if (!isActive) return;

    // POLYMORPHISM - Note-specific interaction
    // Display the note text to the player
    hasBeenRead = true;

    // The UIManager will handle displaying the text
    // (Will be implemented in Player/UIManager interaction)
}
