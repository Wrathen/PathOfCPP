#pragma once
#include <SDL_image.h>
#include <string>
#include "../Miscellaneous/GUID.h"

class BaseRenderer {
    friend class Renderer;
public:
    BaseRenderer();
    void Delete();
    std::string ToString();

private:
    void Render();
    void AssignGUID(GUID _guid) { guid = guid; }

    GUID guid;
    SDL_Rect rect;
    SDL_Texture* tex;
};