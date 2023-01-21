#pragma once
#include <SDL.h>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Vector.h"

#define InputMgr InputManager::GetInstance()
class InputManager : public Singleton<InputManager> { friend class Singleton;
public:
    Vector2 lastMousePos { 0, 0 };

    void Update();
    void OnKeyDown(SDL_Keycode keyCode);
    void OnKeyUp(SDL_Keycode keyCode);
    void OnMouseDown();
    void OnMouseUp();
    void OnMouseMove();

private:
    InputManager() {}
    ~InputManager() {}
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;
};