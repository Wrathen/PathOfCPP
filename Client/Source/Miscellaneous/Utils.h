#pragma once
#include <SDL.h>
#include "Managers/RenderManager.h"
#include "Managers/CameraManager.h"
#include "Managers/GameManager.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Miscellaneous/Time.h"
#include <Core/Game/Entity/Entity.h>
#include "Game/Component/Components.h"

namespace Utils {
	static inline int GetFPS() { return (int)(1.0 / Time::deltaTime); }
	
	static inline void DrawRect(int x, int y, int w, int h, SDL_Color color) {
		SDL_Rect rect{ x, y, w, h };
		SDL_SetRenderDrawColor(MainRenderer.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(MainRenderer.renderer, &rect);
	}
	static inline void FillRect(int x, int y, int w, int h, SDL_Color color) {
		SDL_Rect rect{ x, y, w, h };
		SDL_SetRenderDrawColor(MainRenderer.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(MainRenderer.renderer, &rect);
	}
	static inline void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
		SDL_SetRenderDrawColor(MainRenderer.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(MainRenderer.renderer, x1, y1, x2, y2);
	}

	static inline Core::BaseScene* GetCurrentScene() {
		return Core::SceneMgr.GetCurrentScene();
	}

	static inline entt::registry& GetRegistry() {
		return Utils::GetCurrentScene()->reg;
	}

	static inline Core::Entity GetLocalPlayer() {
		return GAME.GetLocalPlayer();
	}

	static inline Vector2 GetScreenPosition(TransformComponent& transform) {
		return transform.isAbsolutePositioned ? transform.position : transform.position - Camera.GetPosition();
	}
	static inline Vector2 GetScreenPosition(Vector2& pos) {
		return pos - Camera.GetPosition();
	}
}