#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Vector.h"

enum class KeyState {
    EMPTY = 0,
    IsPressed = 1,
    IsHeld = 2,
    IsReleased = 3
};

#define InputMgr InputManager::GetInstance()
class InputManager : public Singleton<InputManager> { 
    friend class Singleton;
    friend class GameManager;
public:
    std::unordered_map<SDL_Keycode, KeyState> keyStates{};
    Vector2 lastMousePos { 0, 0 };

    void Update();
    void LateUpdate();

    bool IsKeyPressed(SDL_Keycode keycode);
    bool IsKeyHeld(SDL_Keycode keycode);
    bool IsKeyReleased(SDL_Keycode keycode);

private:
    // Pressed&released keys this tick.
    std::vector<SDL_Keycode> pressedKeys;
    std::vector<SDL_Keycode> releasedKeys;

    void OnKeyDown(SDL_Keycode keycode);
    void OnKeyUp(SDL_Keycode keycode);
    void OnMouseDown();
    void OnMouseUp();
    void OnMouseMove();

    InputManager() {}
    ~InputManager() {}
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;
};