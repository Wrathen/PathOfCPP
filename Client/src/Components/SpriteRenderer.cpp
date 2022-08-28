#include "SpriteRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Managers/TextureManager.h"
#include "../Managers/CameraManager.h"
#include "../Miscellaneous/Log.h"

void SpriteRenderer::SetVisible(bool flag) { isVisible = flag; }
void SpriteRenderer::AssignTransform(Transform* _transform) { transform = _transform; }
void SpriteRenderer::AssignTexture(SDL_Texture* _tex) { tex = _tex; UpdateTextureDimensions(); }
void SpriteRenderer::AssignTexture(std::string texturePath) { TextureMgr.LoadTexture(texturePath, &tex); UpdateTextureDimensions(); }
void SpriteRenderer::UpdateTextureDimensions() {
    auto textureDimensions = TextureManager::GetDimensions(tex);
    width = textureDimensions.x;
    height = textureDimensions.y;
}
void SpriteRenderer::SetPositionAbsolute() { isAbsolutePositioned = true; }
void SpriteRenderer::SetPositionRelative() { isAbsolutePositioned = false; }

void SpriteRenderer::Render() {
    if (!isVisible || transform == nullptr || tex == nullptr) return;

    // Update Renderer Position
    Vector2 pos = transform->position;
    Vector2 scale = transform->scale;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0, srcRect.y = 0;
    srcRect.w = width, srcRect.h = height;

    destRect.x = pos.x + offset.x;
    destRect.y = pos.y + offset.y;
    destRect.w = srcRect.w * scale.x;
    destRect.h = srcRect.h * scale.y;

    // If set as to be centered, offset the width&height with x&y.
    if (shouldDrawCentered) {
        destRect.x -= destRect.w / 2;
        destRect.y -= destRect.h / 2;
    }

    // Offset by Camera Position
    if (!isAbsolutePositioned) {
        const Vector2& cameraPosition = Camera.GetPosition();
        destRect.x -= cameraPosition.x;
        destRect.y -= cameraPosition.y;
    }

    // Draw
    float rotationDegrees = transform->rotation * 57.2957795;
    SDL_RenderCopyEx(MainRenderer.renderer, tex, &srcRect, &destRect, rotationDegrees, NULL, SDL_FLIP_NONE);
}