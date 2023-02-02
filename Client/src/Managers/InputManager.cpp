#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "../Miscellaneous/Mouse.h"

void InputManager::Update() {
	Vector2 mousePos = Mouse::GetPosition();

	if (lastMousePos.x != mousePos.x || lastMousePos.y != mousePos.y) {
		lastMousePos = mousePos;
		OnMouseMove();
	}
}

void InputManager::OnKeyDown(SDL_Keycode keyCode) {
	Player* player = GAME.GetPlayer();
	if (!player) return;

	switch (keyCode) {
		case SDLK_ESCAPE:
			GAME.Quit();
			break;
		case SDLK_1:
			SceneMgr.ChangeScene("Town");
			break;
		case SDLK_2:
			SceneMgr.ChangeScene("Forest");
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
	// Player Attack State
	Player* player = GAME.GetPlayer();
	if (player) player->CStats->SetAttackingState(true);

	// Notify UIManager
	bool raycast = UIMgr.OnMouseDown();
	if (raycast) return;
}
void InputManager::OnMouseUp() {
	// Player Attack State
	Player* player = GAME.GetPlayer();
	if (player) player->CStats->SetAttackingState(false);

	// Notify UIManager
	//bool raycast = UIMgr.OnMouseUp();
	//if (raycast) return;
}
void InputManager::OnMouseMove() { UIMgr.OnMouseMove(); }