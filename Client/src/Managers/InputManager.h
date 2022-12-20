#pragma once
#include <SDL.h>
#include "../Miscellaneous/Singleton.h"

#define InputMgr InputManager::GetInstance()
class InputManager : public Singleton<InputManager> { friend class Singleton;
public:
    void OnKeyDown(SDL_Keycode keyCode);
    void OnKeyUp(SDL_Keycode keyCode);
    void OnMouseDown();
    void OnMouseUp();

private:
    InputManager() {}
    ~InputManager() {}
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;
};