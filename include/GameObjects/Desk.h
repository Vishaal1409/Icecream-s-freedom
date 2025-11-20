#pragma once

#include "Core/GameObject.h"
#include <string>

/**
 * Desk Class - Interactive furniture with drawers
 *
 * A desk with multiple drawers that can be opened/closed.
 * One drawer contains a hidden clue.
 */
class Desk : public GameObject {
private:
    // Drawer states
    float drawer1OpenProgress;
    float drawer2OpenProgress;
    bool drawer1Open;
    bool drawer2Open;
    float drawerSpeed;

    // Hidden item
    std::string hiddenItemID;
    bool itemCollected;

public:
    // Constructor
    Desk(const std::string& name, Vector3 position);

    // POLYMORPHISM - Override base class methods
    void Update(float deltaTime) override;
    void Render() override;
    void OnInteract(Player* player) override;

    // Drawer control
    void ToggleDrawer1();
    void ToggleDrawer2();

private:
    // Helper methods
    void UpdateDrawerAnimation(float deltaTime);
};
