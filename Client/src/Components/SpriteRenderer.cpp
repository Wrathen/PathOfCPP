#include "SpriteRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Managers/TextureManager.h"
#include "../Managers/CameraManager.h"
#include "../Miscellaneous/Log.h"

// Constructor
SpriteRenderer::SpriteRenderer() : shader{} { shader.Activate(); }

void SpriteRenderer::SetSourceOffset(int x, int y) { sourceOffset.x = x; sourceOffset.y = y; }
void SpriteRenderer::SetSourceOffset(const Vector2& vec) { sourceOffset.x = vec.x; sourceOffset.y = vec.y; }
void SpriteRenderer::SetOffset(int x, int y) { offset.x = x; offset.y = y; }
void SpriteRenderer::SetOffset(const Vector2& vec) { offset.x = vec.x; offset.y = vec.y; }
void SpriteRenderer::SetWidth(unsigned int _w) { width = _w; }
void SpriteRenderer::SetHeight(unsigned int _h) { height = _h; }
void SpriteRenderer::SetScale(float x, float y) { localScale.x = x; localScale.y = y; }
void SpriteRenderer::SetScale(const Vector2& vec) { localScale.x = vec.x; localScale.y = vec.y; }
void SpriteRenderer::SetVisible(bool flag) { isVisible = flag; }


Vector2& SpriteRenderer::GetOffset() { return offset; }
unsigned int SpriteRenderer::GetWidth() { return width; }
unsigned int SpriteRenderer::GetHeight() { return height; }
bool SpriteRenderer::GetVisible() { return isVisible; }

void SpriteRenderer::UpdateTextureDimensions() {
    auto textureDimensions = TextureManager::GetDimensions(img);
    width = textureDimensions.x;
    height = textureDimensions.y;

	// Set the shader variable resolution.
	float resolution[2] = { (float)width, (float)height };
	GPU_SetUniformfv(shader.GetVariableLocation("resolution"), 2, 1, resolution);

	// Set the shader image
	shader.SetImage(img);
}

void SpriteRenderer::AssignTransform(Transform* _transform) { 
    transform = _transform;
    transform->isAbsolutePositioned = isAbsolutePositioned;
}
void SpriteRenderer::AssignTexture(GPU_Image* _img) { img = _img; UpdateTextureDimensions(); }
void SpriteRenderer::AssignTexture(std::string texturePath) { 
    TextureMgr.LoadTexture(texturePath, &img); 
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
void SpriteRenderer::SetColor(SDL_Color _color) { color = _color; if (!color.a) color.a = 255; }
void SpriteRenderer::SetShadow(unsigned int _size, SDL_Color _shadowColor) {
	isShadowEnabled = true;
	shadowSize = _size;
	shadowColor = _shadowColor;
}

void SpriteRenderer::SetSourceAndDestinationRects() {
    // Update Renderer Position
    Vector2 pos = transform->GetScreenPosition();
    Vector2 transformScale = transform->GetScale();

    srcRect.x = sourceOffset.x; 
    srcRect.y = sourceOffset.y;
    srcRect.w = width;
    srcRect.h = height;

    destRect.x = pos.x + offset.x;
    destRect.y = pos.y + offset.y;
    destRect.w = transformScale.x * localScale.x;
    destRect.h = transformScale.y * localScale.y;

	// If set as to be centered, offset the width&height with x&y.
    if (shouldDrawCentered) {
        destRect.x -= destRect.w / 2;
        destRect.y -= destRect.h / 2;
    }
}
void SpriteRenderer::Render() {
    if (!isVisible || transform == nullptr || img == nullptr) return;

    // Set Source and Destination Rects
    SetSourceAndDestinationRects();

	// Calculate the Rotation in Degrees.
	float rotationDegrees = transform->rotation * 57.2957795f; // radians to degrees formula

	// Update Shader variables
	static uint32_t cached_GlobalTimeLocation = shader.GetVariableLocation("globalTime");
	GPU_SetUniformf(cached_GlobalTimeLocation, SDL_GetTicks());

	// Render Shadows.
	if (false && isShadowEnabled && shadowSize > 0) {
		GPU_Rect shadowDestRect = destRect;
		shadowDestRect.x -= 2;
		shadowDestRect.y -= 2;
		shadowDestRect.w += 2;
		shadowDestRect.h += 2;
		
		GPU_SetRGBA(img, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
		GPU_BlitTransform(img, &srcRect, MainRenderer.target, shadowDestRect.x, shadowDestRect.y, rotationDegrees, shadowDestRect.w, shadowDestRect.h);
	}

    // Render Sprite.
	GPU_SetRGBA(img, color.r, color.g, color.b, color.a);
	GPU_BlitTransform(img, &srcRect, MainRenderer.target, destRect.x, destRect.y, rotationDegrees, destRect.w, destRect.h);
}