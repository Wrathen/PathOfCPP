#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"

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
	Player* player = GAME.GetPlayer();
	if (player) player->GetStats()->isAttacking = true;
}
void InputManager::OnMouseUp() {
	Player* player = GAME.GetPlayer();
	if (player) player->GetStats()->isAttacking = false;
}