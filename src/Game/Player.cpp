#include "Game/Player.h"
#include "raymath.h"

Player::Player(Vector3 startPosition, CollisionSystem* collision)
    : velocity({0, 0, 0})
    , moveSpeed(3.0f)
    , mouseSensitivity(0.1f)
    , controlsLocked(false)
    , collisionSystem(collision) {

    // COMPOSITION - Initialize camera (HAS-A relationship)
    camera.position = startPosition;
    camera.target = Vector3Add(startPosition, {0, 0, -1});
    camera.up = {0, 1, 0};
    camera.fovy = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // COMPOSITION - Create inventory (HAS-A relationship)
    inventory = std::make_unique<Inventory>();
}

void Player::Update(float deltaTime) {
    if (controlsLocked) return;

    HandleInput(deltaTime);
    UpdateCameraMovement(deltaTime);
    UpdateMouseLook();
}

void Player::HandleInput(float deltaTime) {
    if (controlsLocked) return;

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    forward.y = 0;  // Keep movement on XZ plane
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    Vector3 moveDirection = {0, 0, 0};

    // WASD movement
    if (IsKeyDown(KEY_W)) {
        moveDirection = Vector3Add(moveDirection, forward);
    }
    if (IsKeyDown(KEY_S)) {
        moveDirection = Vector3Subtract(moveDirection, forward);
    }
    if (IsKeyDown(KEY_A)) {
        moveDirection = Vector3Subtract(moveDirection, right);
    }
    if (IsKeyDown(KEY_D)) {
        moveDirection = Vector3Add(moveDirection, right);
    }

    // Normalize to prevent faster diagonal movement
    if (Vector3Length(moveDirection) > 0) {
        moveDirection = Vector3Normalize(moveDirection);
        Move(moveDirection, deltaTime);
    }
}

void Player::Move(Vector3 direction, float deltaTime) {
    Vector3 movement = Vector3Scale(direction, moveSpeed * deltaTime);
    Vector3 newPosition = Vector3Add(camera.position, movement);

    // Check collision with room boundaries
    if (collisionSystem) {
        newPosition = collisionSystem->CheckBoundaries(newPosition);
    }

    // Update camera position and target
    Vector3 delta = Vector3Subtract(newPosition, camera.position);
    camera.position = newPosition;
    camera.target = Vector3Add(camera.target, delta);
}

void Player::UpdateCameraMovement(float deltaTime) {
    // Smooth velocity decay (friction)
    velocity = Vector3Scale(velocity, 1.0f - (10.0f * deltaTime));
}

void Player::UpdateMouseLook() {
    if (controlsLocked) return;

    Vector2 mouseDelta = GetMouseDelta();

    if (Vector2Length(mouseDelta) > 0) {
        // Horizontal rotation (yaw)
        float angleX = mouseDelta.x * mouseSensitivity * DEG2RAD;

        // Calculate current direction
        Vector3 direction = Vector3Subtract(camera.target, camera.position);
        float distance = Vector3Length(direction);

        // Rotate around Y axis
        Matrix rotation = MatrixRotateY(-angleX);
        direction = Vector3Transform(direction, rotation);

        // Vertical rotation (pitch)
        Vector3 right = Vector3CrossProduct(direction, camera.up);
        right = Vector3Normalize(right);
        float angleY = mouseDelta.y * mouseSensitivity * DEG2RAD;

        Matrix pitchRotation = MatrixRotate(right, -angleY);
        Vector3 newDirection = Vector3Transform(direction, pitchRotation);

        // Limit pitch to prevent flipping
        float pitch = asinf(newDirection.y / Vector3Length(newDirection));
        if (pitch < 1.4f && pitch > -1.4f) {  // ~80 degrees limit
            direction = newDirection;
        }

        // Update camera target
        camera.target = Vector3Add(camera.position, Vector3Normalize(direction));
    }
}
