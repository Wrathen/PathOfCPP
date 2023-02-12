#include "SpriteRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Managers/TextureManager.h"
#include "../Managers/CameraManager.h"
#include "../Miscellaneous/Log.h"

void SpriteRenderer::SetSourceOffset(int x, int y) { sourceOffset.x = x; sourceOffset.y = y; }
void SpriteRenderer::SetSourceOffset(const Vector2& vec) { sourceOffset.x = vec.x; sourceOffset.y = vec.y; }
void SpriteRenderer::SetOffset(int x, int y) { offset.x = x; offset.y = y; }
void SpriteRenderer::SetOffset(const Vector2& vec) { offset.x = vec.x; offset.y = vec.y; }
void SpriteRenderer::SetWidth(unsigned int _w) { width = _w; }
void SpriteRenderer::SetHeight(unsigned int _h) { height = _h; }
void SpriteRenderer::SetVisible(bool flag) { isVisible = flag; }

Vector2& SpriteRenderer::GetOffset() { return offset; }
unsigned int SpriteRenderer::GetWidth() { return width; }
unsigned int SpriteRenderer::GetHeight() { return height; }
bool SpriteRenderer::GetVisible() { return isVisible; }

void SpriteRenderer::UpdateTextureDimensions() {
    auto textureDimensions = TextureManager::GetDimensions(tex);
    width = textureDimensions.x;
    height = textureDimensions.y;
}

void SpriteRenderer::AssignTransform(Transform* _transform) { 
    transform = _transform;
    transform->isAbsolutePositioned = isAbsolutePositioned;
}
void SpriteRenderer::AssignTexture(SDL_Texture* _tex) { tex = _tex; UpdateTextureDimensions(); }
void SpriteRenderer::AssignTexture(std::string texturePath) { 
    TextureMgr.LoadTexture(texturePath, &tex); 
    UpdateTextureDimensions();
}

void SpriteRenderer::SetPositionAbsolute() { 
    if (transform) transform->isAbsolutePositioned = true; 
    isAbsolutePositioned = true; 
}
void SpriteRenderer::SetPositionRelative() { 
    if (transform) transform->isAbsolutePositioned = false;
    isAbsolutePositioned = false; 
}
void SpriteRenderer::SetColor(int r, int g, int b) { 
    if (!tex) return; 
    SDL_SetTextureColorMod(tex, r, g, b);
}

void SpriteRenderer::SetSourceAndDestinationRects() {
    // Update Renderer Position
    Vector2 pos = transform->GetScreenPosition();
    Vector2 scale = transform->GetScale();

    srcRect.x = sourceOffset.x; 
    srcRect.y = sourceOffset.y;
    srcRect.w = width;
    srcRect.h = height;

    destRect.x = pos.x + offset.x;
    destRect.y = pos.y + offset.y;
    destRect.w = srcRect.w * scale.x;
    destRect.h = srcRect.h * scale.y;
}
void SpriteRenderer::Render() {
    if (!isVisible || transform == nullptr || tex == nullptr) return;

    // Set Source and Destination Rects
    SetSourceAndDestinationRects();

    // If set as to be centered, offset the width&height with x&y.
    if (shouldDrawCentered) {
        destRect.x -= destRect.w / 2;
        destRect.y -= destRect.h / 2;
    }

    // Draw
    float rotationDegrees = transform->rotation * 57.2957795; // radians to degrees formula
    SDL_RenderCopyEx(MainRenderer.renderer, tex, &srcRect, &destRect, 
        rotationDegrees, NULL, isFlipped ? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);
}