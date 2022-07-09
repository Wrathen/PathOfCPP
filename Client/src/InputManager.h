#pragma once
#include <SDL2/SDL.h>

#define InputMgr InputManager::GetInstance()
class InputManager {
public:
    static InputManager& GetInstance() {
        static InputManager instance;
        return instance;
    }
    void OnKeyDown(SDL_Keycode keyCode);
    void OnKeyUp(SDL_Keycode keyCode);

private:
    InputManager() {};
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;
};