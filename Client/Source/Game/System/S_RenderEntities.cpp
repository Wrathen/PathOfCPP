#include "S_RenderEntities.h"
#include <iostream>
#include "Core/Managers/SceneManager.h"
#include "Game/Component/Components.h"
#include <Managers/CameraManager.h>
#include "Miscellaneous/Utils.h"

void S_RenderEntities::Start() {

}

void S_RenderEntities::Update() {
	auto& reg = Utils::GetRegistry();
	auto group = reg.group<SpriteRendererComponent>(entt::get<TransformComponent, TextureComponent>);

	group.each([](auto entity, auto& renderer, auto& transform, auto& tex) {
		if (!renderer.isVisible || !tex.texture)
			return;

		// Set Source and Destination Rects
		{
			// Update Renderer Position // below is transform.GetScreenPosition()
			Vector2 pos = transform.isAbsolutePositioned ? (transform.position) : (transform.position) - Camera.GetPosition();
			Vector2 transformScale = transform.scale;

			renderer.srcRect.x = (int)renderer.sourceOffset.x;
			renderer.srcRect.y = (int)renderer.sourceOffset.y;
			renderer.srcRect.w = renderer.width;
			renderer.srcRect.h = renderer.height;

			renderer.destRect.x = (int)(pos.x + renderer.offset.x);
			renderer.destRect.y = (int)(pos.y + renderer.offset.y);
			renderer.destRect.w = (int)(renderer.srcRect.w * transformScale.x * renderer.localScale.x);
			renderer.destRect.h = (int)(renderer.srcRect.h * transformScale.y * renderer.localScale.y);

			// If set as to be centered, offset the width&height with x&y.
			if (renderer.shouldDrawCentered) {
				renderer.destRect.x -= renderer.destRect.w / 2;
				renderer.destRect.y -= renderer.destRect.h / 2;
			}
		}

		// Calculate the Rotation in Degrees.
		float rotationDegrees = transform.rotation * 57.2957795f; // radians to degrees formula

		// Render Sprite.
		SDL_SetTextureColorMod(tex.texture, renderer.color.r, renderer.color.g, renderer.color.b);
		SDL_SetTextureAlphaMod(tex.texture, renderer.color.a);
		SDL_RenderCopyEx(MainRenderer.renderer, tex.texture, &renderer.srcRect, &renderer.destRect,
			rotationDegrees, NULL, renderer.isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	});
}

void S_RenderEntities::LateUpdate() {

}

void S_RenderEntities::Destroy() {
}