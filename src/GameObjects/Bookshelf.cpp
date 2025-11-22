#include "GameObjects/Bookshelf.h"
#include "Game/Player.h"

Bookshelf::Bookshelf(const std::string& name, Vector3 position, bool containsSecret)
    : GameObject(name, position, true)
    , hasSecret(containsSecret)
    , secretRevealed(false) {

    color = DARKBROWN;
}

void Bookshelf::Update([[maybe_unused]] float deltaTime) {
    if (!isActive) return;
    // No specific update needed
}

void Bookshelf::Render() {
    if (!isActive) return;

    Vector3 pos = transform.GetPosition();
    Color renderColor = isHighlighted ? ORANGE : color;

    // Draw main bookshelf frame
    DrawCube({pos.x, pos.y, pos.z}, 0.6f, 1.2f, 0.3f, renderColor);

    // Draw shelves (3 shelves)
    for (int i = 0; i < 3; i++) {
        float shelfY = pos.y + 0.2f - (i * 0.35f);
        DrawCube({pos.x, shelfY, pos.z}, 0.55f, 0.03f, 0.25f, DARKGRAY);
    }

    // Draw books (simple colored boxes)
    for (int shelf = 0; shelf < 3; shelf++) {
        float shelfY = pos.y + 0.1f - (shelf * 0.35f);

        for (int bookIdx = 0; bookIdx < 4; bookIdx++) {
            float bookX = pos.x - 0.15f + (bookIdx * 0.1f);
            Color bookColor = hasSecret && shelf == 1 && bookIdx == 2 ? GOLD : BROWN;
            DrawCube({bookX, shelfY, pos.z}, 0.08f, 0.15f, 0.02f, bookColor);
        }
    }
}

void Bookshelf::OnInteract([[maybe_unused]] Player* player) {
    if (!isActive) return;

    if (hasSecret && !secretRevealed) {
        RevealSecret();
        // Secret was revealed - player found the clue!
    }
}
