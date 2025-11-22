#pragma once

#include "raylib.h"

/**
 * Room Class - Demonstrates ENCAPSULATION
 *
 * Encapsulates all room geometry and rendering.
 * Keeps room details private, exposes only necessary interface.
 */
class Room {
private:
    // ENCAPSULATION - Private room properties
    float width;
    float height;
    float depth;
    Vector3 center;

    // Colors
    Color floorColor;
    Color wallColor;
    Color ceilingColor;

public:
    Room(float w = 10.0f, float h = 4.0f, float d = 10.0f);
    ~Room() = default;

    // Render the room
    void Render();

    // ENCAPSULATION - Getters
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetDepth() const { return depth; }
    Vector3 GetMin() const;
    Vector3 GetMax() const;

private:
    // ENCAPSULATION - Private rendering methods
    void RenderFloor();
    void RenderCeiling();
    void RenderWalls();
    void RenderDecorations();
};
