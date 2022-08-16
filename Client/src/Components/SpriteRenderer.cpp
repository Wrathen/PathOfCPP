#include "SpriteRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Managers/TextureManager.h"
#include "../Managers/CameraManager.h"

SpriteRenderer::SpriteRenderer() {}
SpriteRenderer::~SpriteRenderer() { SDL_DestroyTexture(tex); }

void SpriteRenderer::SetVisible(bool flag) { isVisible = flag; }
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
    TextureMgr.LoadTexture(texturePath, &tex);
}

void SpriteRenderer::Render() {
    if (!isVisible || transform == nullptr || tex == nullptr) return;

    // Update Renderer Position
    Vector2 pos = transform->position;
    srcRect.x = 0, srcRect.y = 0;
    srcRect.w = 32, srcRect.h = 32;

    // Offset by Camera Position
    Vector2 cameraPosition = Camera.GetPosition();
    destRect.x = pos.x - cameraPosition.x;
    destRect.y = pos.y - cameraPosition.y;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;

    // Draw
    SDL_RenderCopyEx(MainRenderer.renderer, tex, &srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
}