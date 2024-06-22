#pragma once
#include <SDL.h>
#include <unordered_map>
#include <functional>
#include <vector>
#include "Core/Miscellaneous/Vector.h"
#include "Core/Miscellaneous/Timer.h"

enum class KeyState {
    EMPTY = 0,
    IsPressed = 1,
    IsHeld = 2,
    IsReleased = 3
};

#define InputMgr InputManager::GetInstance()
class InputManager { friend class GameManager;
public:
    static InputManager& GetInstance() { static InputManager _i; return _i; }

    std::unordered_map<SDL_Keycode, KeyState> keyStates{};
    std::function<void()> onMouseDown = nullptr;
    std::function<void()> onMouseUp = nullptr;
    std::function<void()> onMouseMove = nullptr;
    Vector2 lastMousePos{ 0, 0 };

    // Base Functions
    void Update();
    void LateUpdate();

    // Main Functions
    void DisableMouse(float duration);
    bool IsKeyPressed(SDL_Keycode keycode);
    bool IsKeyHeld(SDL_Keycode keycode);
    bool IsKeyReleased(SDL_Keycode keycode);
    bool IsMouseHeld();

private:
    // Pressed&released keys this tick.
    std::vector<SDL_Keycode> pressedKeys;
    std::vector<SDL_Keycode> releasedKeys;
    double mouseEventsDisableCountdown = 0;
    bool isMouseEventsDisabled = false;
    bool isMouseHeld = false;

    // Events
    void OnKeyDown(SDL_Keycode keycode);
    void OnKeyUp(SDL_Keycode keycode);
    void OnMouseDown();
    void OnMouseUp();
    void OnMouseMove();

    // Ctor & Dtor
    InputManager() {}
    ~InputManager() {}
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;
};