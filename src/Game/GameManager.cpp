#include "GameManager.h"
#include "GameObjects/Key.h"
#include "GameObjects/Door.h"
#include "GameObjects/Note.h"
#include "GameObjects/Puzzle.h"
#include "GameObjects/Chest.h"
#include "GameObjects/Desk.h"
#include "GameObjects/Bookshelf.h"
#include "GameObjects/Safe.h"

GameManager::GameManager()
    : uiManager(UIManager::GetInstance())
    , isPaused(false)
    , gameWon(false)
    , isCursorLocked(false)
    , gameTime(0.0f) {

    stateManager = std::make_unique<GameStateManager>();
    Initialize();
}

void GameManager::Initialize() {
    InitializeSystems();
    CreateGameObjects();
    SetupLighting();
    stateManager->SetState(GameState::PLAYING);
}

void GameManager::InitializeSystems() {
    // COMPOSITION - Create and initialize all subsystems

    // Create room
    room = std::make_unique<Room>(10.0f, 4.0f, 10.0f);

    // Create collision system with room bounds
    collisionSystem = std::make_unique<CollisionSystem>(room->GetMin(), room->GetMax(), 0.5f);

    // Create player at starting position
    player = std::make_unique<Player>(Vector3{0, 1.6f, 5}, collisionSystem.get());

    // Create interaction system
    interactionSystem = std::make_unique<InteractionSystem>();
}

void GameManager::CreateGameObjects() {
    CreateKeys();
    CreateNotes();
    CreatePuzzle();
    CreatePuzzles();  // Add new advanced puzzle types
    CreateChest();
    CreateDoors();

    // Add furniture objects for richer environment
    auto desk = std::make_unique<Desk>("Desk", Vector3{-2.5f, 0.0f, 2.5f});
    interactionSystem->RegisterObject(desk.get());
    gameObjects.push_back(std::move(desk));

    auto bookshelf = std::make_unique<Bookshelf>("Bookshelf", Vector3{3.5f, 0.0f, -1.0f}, true);
    interactionSystem->RegisterObject(bookshelf.get());
    gameObjects.push_back(std::move(bookshelf));

    auto safe = std::make_unique<Safe>("WallSafe", Vector3{4.5f, 1.8f, 0.0f}, "5432");
    interactionSystem->RegisterObject(safe.get());
    gameObjects.push_back(std::move(safe));
}

void GameManager::CreateKeys() {
    // Red Key - on the table
    auto redKey = std::make_unique<Key>("red", Vector3{-3, 0.9f, -2}, RED);
    interactionSystem->RegisterObject(redKey.get());
    gameObjects.push_back(std::move(redKey));

    // Blue Key - on the floor in corner
    auto blueKey = std::make_unique<Key>("blue", Vector3{3, 0.2f, 3}, BLUE);
    interactionSystem->RegisterObject(blueKey.get());
    gameObjects.push_back(std::move(blueKey));
}

void GameManager::CreateNotes() {
    // Note 1 - Clue about the year
    auto note1 = std::make_unique<Note>(
        "Note1",
        Vector3{-3.5f, 1.2f, -4.5f},
        "My dearest friend,\n\nRemember the year Hamilton-Fish\nwas born?\n\nOctober 18, 1842.\n\nI'll never forget it.\n\n- J."
    );
    interactionSystem->RegisterObject(note1.get());
    gameObjects.push_back(std::move(note1));

    // Note 2 - Direct code hint
    auto note2 = std::make_unique<Note>(
        "Note2",
        Vector3{2, 0.5f, 2},
        "Diary Entry - March 5th\n\nThe wall safe code keeps\nslipping my mind.\n\nI wrote it down: 1-8-4-2\n\nDon't forget this time!"
    );
    interactionSystem->RegisterObject(note2.get());
    gameObjects.push_back(std::move(note2));
}

void GameManager::CreatePuzzle() {
    // Code Lock Puzzle on east wall
    auto puzzle = std::make_unique<Puzzle>("CodeLock", Vector3{4.5f, 1.5f, 0}, "1842");

    // Set callback for when puzzle is solved
    puzzle->SetOnSolveCallback([this]() {
        uiManager.ShowMessage("Puzzle solved! You hear a click...", 4.0f);
    });

    interactionSystem->RegisterObject(puzzle.get());
    gameObjects.push_back(std::move(puzzle));
}

void GameManager::CreatePuzzles() {
    // Simon Says Memory Puzzle
    auto simonPuzzle = std::make_unique<SimonSaysPuzzle>("SimonSays", Vector3{-1.5f, 1.5f, -4.5f});
    interactionSystem->RegisterObject(simonPuzzle.get());
    gameObjects.push_back(std::move(simonPuzzle));

    // Pattern Rotation Puzzle
    auto patternPuzzle = std::make_unique<PatternPuzzle>("PatternLock", Vector3{2.0f, 1.5f, -4.5f});
    interactionSystem->RegisterObject(patternPuzzle.get());
    gameObjects.push_back(std::move(patternPuzzle));

    // Light Switch Puzzle
    auto lightPuzzle = std::make_unique<LightSwitchPuzzle>("LightPanel", Vector3{-4.5f, 1.5f, 2.5f});
    interactionSystem->RegisterObject(lightPuzzle.get());
    gameObjects.push_back(std::move(lightPuzzle));
}

void GameManager::CreateChest() {
    // Chest locked with blue key, contains gold key
    auto chest = std::make_unique<Chest>("Chest", Vector3{-2, 0.3f, -3.5f}, "blue", "gold");
    interactionSystem->RegisterObject(chest.get());
    gameObjects.push_back(std::move(chest));
}

void GameManager::CreateDoors() {
    // Exit door (requires gold key) - WIN CONDITION
    auto exitDoor = std::make_unique<Door>("ExitDoor", Vector3{0, 1.5f, -4.95f}, "gold", true);
    interactionSystem->RegisterObject(exitDoor.get());
    gameObjects.push_back(std::move(exitDoor));

    // Regular unlocked door (demonstration)
    auto regularDoor = std::make_unique<Door>("RegularDoor", Vector3{-4.95f, 1.5f, 0}, "", false);
    interactionSystem->RegisterObject(regularDoor.get());
    gameObjects.push_back(std::move(regularDoor));
}

void GameManager::SetupLighting() {
    // Raylib will use default lighting
    // For better lighting, could implement custom shaders
}

void GameManager::Update(float deltaTime) {
    // Update game state manager
    stateManager->Update(deltaTime);

    if (gameWon) return;

    // Track elapsed game time
    if (!isPaused && !uiManager.IsPauseMenuActive()) {
        gameTime += deltaTime;
    }

    // Update UIManager with game time
    uiManager.SetGameTime(gameTime);

    // Update UI
    uiManager.Update(deltaTime);

    // Update cursor lock state based on game state
    UpdateCursorState();

    // Don't update game state if paused
    if (isPaused || uiManager.IsPauseMenuActive()) return;

    // Update player
    if (!uiManager.IsAnyUIActive()) {
        player->Update(deltaTime);
    }

    // POLYMORPHISM - Update all game objects through base class pointer
    for (auto& obj : gameObjects) {
        obj->Update(deltaTime);
    }

    // Update interaction system
    if (!uiManager.IsAnyUIActive()) {
        interactionSystem->Update(player->GetCamera());
    }

    // Handle input
    HandleInput();

    // Check win condition
    CheckWinCondition();
}

void GameManager::Render() {
    BeginMode3D(player->GetCamera());

    // Render room
    room->Render();

    // POLYMORPHISM - Render all game objects through base class pointer
    for (auto& obj : gameObjects) {
        if (obj->IsActive()) {
            obj->Render();
        }
    }

    EndMode3D();

    // Render UI
    bool hasTarget = interactionSystem->GetCurrentTarget() != nullptr;
    uiManager.RenderUI(player->GetInventory(), hasTarget);
}

void GameManager::HandleInput() {
    if (gameWon) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }
        return;
    }

    // Handle P key for pause menu
    if (IsKeyPressed(KEY_P)) {
        uiManager.TogglePauseMenu();
        isPaused = uiManager.IsPauseMenuActive();
    }

    // Handle ESC key
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (uiManager.IsPauseMenuActive()) {
            uiManager.ClosePauseMenu();
            isPaused = false;
        } else if (uiManager.IsAnyUIActive()) {
            // Close active UI
            uiManager.HideNote();
            uiManager.HideCodeInputUI();
        } else {
            // Quit game
            CloseWindow();
        }
    }

    // Handle H key for hints
    if (IsKeyPressed(KEY_H)) {
        uiManager.ShowNextHint();
    }

    // Don't handle game input if UI is active or paused
    if (uiManager.IsAnyUIActive() || isPaused) {
        HandleCodeInput();
        return;
    }

    // Handle interaction
    HandleInteractionInput();
}

void GameManager::HandleInteractionInput() {
    if (IsKeyPressed(KEY_E)) {
        GameObject* target = interactionSystem->GetCurrentTarget();
        if (target) {
            // Check what type of object and handle accordingly
            if (Key* key = dynamic_cast<Key*>(target)) {
                key->OnInteract(player.get());
                player->GetInventory().AddItem(key->GetKeyID());
                uiManager.ShowMessage("Collected " + key->GetKeyID() + " key!");
            }
            else if (Note* note = dynamic_cast<Note*>(target)) {
                note->OnInteract(player.get());
                uiManager.ShowNote(note->GetNoteText());
            }
            else if (Puzzle* puzzle = dynamic_cast<Puzzle*>(target)) {
                puzzle->OnInteract(player.get());
                uiManager.ShowCodeInputUI();
            }
            else if (Door* door = dynamic_cast<Door*>(target)) {
                if (door->IsLocked()) {
                    if (player->GetInventory().HasItem(door->GetRequiredKeyID())) {
                        // ENCAPSULATION - Let door handle its own unlocking via Unlock() method
                        door->Unlock();  // Sets locked=false and starts opening animation
                        uiManager.ShowMessage("Door unlocked!");

                        // Check if exit door (win condition)
                        if (door->IsExitDoor()) {
                            gameWon = true;
                            uiManager.ShowWin();
                        }
                    } else {
                        uiManager.ShowMessage("This door requires the " + door->GetRequiredKeyID() + " key");
                    }
                } else {
                    // Door is already unlocked, just open it
                    door->OnInteract(player.get());
                }
            }
            else if (Chest* chest = dynamic_cast<Chest*>(target)) {
                if (chest->IsLocked()) {
                    if (player->GetInventory().HasItem(chest->GetRequiredKeyID())) {
                        // ENCAPSULATION - Let chest handle its own unlocking via Unlock() method
                        chest->Unlock();  // Sets locked=false and starts opening animation
                        uiManager.ShowMessage("Chest unlocked!");

                        // Add contained item to inventory
                        player->GetInventory().AddItem(chest->GetContainedItemID());
                        uiManager.ShowMessage("Found " + chest->GetContainedItemID() + " key in chest!", 4.0f);
                    } else {
                        uiManager.ShowMessage("This chest requires the " + chest->GetRequiredKeyID() + " key");
                    }
                } else {
                    uiManager.ShowMessage("The chest is empty");
                }
            }
        }
    }
}

void GameManager::HandleCodeInput() {
    if (!uiManager.IsCodeInputActive()) return;

    // Number keys 0-9
    for (int i = 0; i <= 9; i++) {
        if (IsKeyPressed(KEY_ZERO + i) || IsKeyPressed(KEY_KP_0 + i)) {
            uiManager.AddCodeDigit('0' + i);
        }
    }

    // Backspace to clear
    if (IsKeyPressed(KEY_BACKSPACE)) {
        uiManager.ClearCodeInput();
    }

    // Enter to submit
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        std::string code = uiManager.GetCodeInput();
        if (code.length() == 4) {
            // Find the puzzle and submit code (let Puzzle class validate it)
            for (auto& obj : gameObjects) {
                if (Puzzle* puzzle = dynamic_cast<Puzzle*>(obj.get())) {
                    if (puzzle->IsInputActive()) {
                        // ENCAPSULATION - Let the Puzzle class handle validation
                        // Add digits and submit - Puzzle::CheckCode() handles validation
                        for (char digit : code) {
                            puzzle->AddDigit(digit);
                        }
                        puzzle->SubmitCode();

                        // Show feedback based on puzzle result
                        if (puzzle->IsSolved()) {
                            uiManager.ShowMessage("Correct code!", 3.0f);
                        } else {
                            uiManager.ShowMessage("Incorrect code!", 2.0f);
                        }
                        break;
                    }
                }
            }
            uiManager.HideCodeInputUI();
        }
    }
}

void GameManager::CheckWinCondition() {
    // Win condition is handled when exit door is opened
}

void GameManager::UpdateCursorState() {
    // Lock cursor during gameplay, unlock during menus/UI
    bool shouldLockCursor = !gameWon && !uiManager.IsAnyUIActive();

    if (shouldLockCursor && !isCursorLocked) {
        DisableCursor();  // Lock cursor for FPS controls
        isCursorLocked = true;
    } else if (!shouldLockCursor && isCursorLocked) {
        EnableCursor();   // Unlock cursor for menus
        isCursorLocked = false;
    }
}
