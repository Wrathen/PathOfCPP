#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "UIManager.h"

void InputManager::OnKeyDown(SDL_Keycode keyCode) {
	Player* player = GAME.GetPlayer();
	if (!player) return;

	switch (keyCode) {
		case SDLK_ESCAPE:
			GAME.Quit();
			break;
		case SDLK_w:
			player->transform.velocity.y -= 1;
			break;
		case SDLK_s:
			player->transform.velocity.y += 1;
			break;
		case SDLK_a:
			player->transform.velocity.x -= 1;
			break;
		case SDLK_d:
			player->transform.velocity.x += 1;
			break;
	}
}
void InputManager::OnKeyUp(SDL_Keycode keyCode) {
	Player* player = GAME.GetPlayer();
	if (!player) return;

	switch (keyCode) {
		case SDLK_w:
			player->transform.velocity.y += 1;
			break;
		case SDLK_s:
			player->transform.velocity.y -= 1;
			break;
		case SDLK_a:
			player->transform.velocity.x += 1;
			break;
		case SDLK_d:
			player->transform.velocity.x -= 1;
			break;
	}
}

void InputManager::OnMouseDown() {
	// Notify UIManager
	bool raycast = UIMgr.OnMouseDown(); // bunu yaz
	if (raycast) return; // If we clicked any UI Element, we shouldn't fire arrows

	// Player Attack State
	Player* player = GAME.GetPlayer();
	if (player) player->SetAttackingState(true);
}
void InputManager::OnMouseUp() {
	// Notify UIManager
	bool raycast = UIMgr.OnMouseDown();
	if (raycast) return; // If we clicked any UI Element, we shouldn't fire arrows

	// Player Attack State
	Player* player = GAME.GetPlayer();
	if (player) player->SetAttackingState(false);
}