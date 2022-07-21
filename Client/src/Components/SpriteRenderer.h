#pragma once
#include <SDL_image.h>
#include <string>
#include "../Miscellaneous/GUID.h"
#include "Transform.h"

class SpriteRenderer {
    friend class Renderer;
public:
    SpriteRenderer();
    ~SpriteRenderer();
    void AssignTexture(SDL_Texture* _tex);
    void AssignTexture(std::string path);
    void AssignTransform(Transform* _transform);
    void Render();

    Transform* transform = nullptr;
    SDL_Texture* tex = nullptr;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};