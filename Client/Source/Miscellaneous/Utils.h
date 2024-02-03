#pragma once
#include <SDL.h>
#include "Managers/RenderManager.h"
#include "Core/Miscellaneous/Vector.h"
#include "Core/Miscellaneous/Time.h"
#include "Core/Managers/SceneManager.h"


namespace Utils {
	static inline int GetFPS() { return (int)(1.0 / Time::deltaTime); }
	
	//void DrawRect(Vector2 pos, int w, int h, SDL_Color color) { DrawRect(pos.x, pos.y, w, h, color); }
	//void DrawRect(Rect rect, SDL_Color color) { DrawRect(rect.x, rect.y, rect.w, rect.h, color); }
	static inline void DrawRect(int x, int y, int w, int h, SDL_Color color) {
		SDL_Rect rect{ x, y, w, h };
		SDL_SetRenderDrawColor(MainRenderer.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(MainRenderer.renderer, &rect);
	}

	static inline Core::BaseScene* GetCurrentScene() {
		return Core::SceneMgr.GetCurrentScene();
	}

	static inline entt::registry& GetRegistry() {
		return GetCurrentScene()->reg;
	}
}