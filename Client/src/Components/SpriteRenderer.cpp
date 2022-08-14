#include "SpriteRenderer.h"
#include "../Managers/RenderManager.h"

SpriteRenderer::SpriteRenderer() {}
SpriteRenderer::~SpriteRenderer() { SDL_DestroyTexture(tex); }

void SpriteRenderer::AssignTransform(Transform* _transform) { transform = _transform; }
void SpriteRenderer::AssignTexture(SDL_Texture* _tex) {
    if (tex != nullptr && tex != _tex) {
        GAME.Debug("[WARNING] Trying to eliminate Possible Memory Leak!");
        SDL_DestroyTexture(tex);
    }

    tex = _tex;
}
void SpriteRenderer::AssignTexture(std::string texturePath) {
    if (tex != nullptr) {
        GAME.Debug("[ERROR] Already assigned a texture to this entity!");
        return;
    }
    Renderer::LoadTexture(texturePath, &tex);
}

void SpriteRenderer::Render() {
    if (transform == nullptr || tex == nullptr) return;

    // Update Renderer Position
    Vector2 pos = transform->position;
    srcRect.x = 0, srcRect.y = 0;
    srcRect.w = 32, srcRect.h = 32;
    destRect.x = pos.x;
    destRect.y = pos.y;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;

    // Draw
    SDL_RenderCopyEx(MainRenderer.renderer, tex, &srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
}