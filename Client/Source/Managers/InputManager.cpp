#include "InputManager.h"
#include "GameManager.h"
//#include "EntityManager.h"
//#include "UIManager.h"
#include "Miscellaneous/Mouse.h"

void InputManager::Update() {
	Vector2 mousePos = Mouse::GetPosition();

	// If the mouse has moved in the last frame, call the OnMouseMove event.
	if (lastMousePos.x != mousePos.x || lastMousePos.y != mousePos.y) {
		lastMousePos = mousePos;
		OnMouseMove();
	}

	// Handle disabling mouse events for duration.
	if (isMouseEventsDisabled) {
		if (mouseEventsDisableCountdown > 0.0f)
			mouseEventsDisableCountdown -= Time::deltaTime;
		if (mouseEventsDisableCountdown < 0.0f)
			isMouseEventsDisabled = false;
	}
}
void InputManager::LateUpdate() {
	for (auto key : pressedKeys)
		keyStates[key] = KeyState::IsHeld;

	for (auto key : releasedKeys)
		keyStates[key] = KeyState::EMPTY;

	pressedKeys.clear();
	releasedKeys.clear();
}

void InputManager::DisableMouse(float duration) {
	mouseEventsDisableCountdown = duration;
	isMouseEventsDisabled = true;
}

void InputManager::OnKeyDown(SDL_Keycode keycode) {
	keyStates[keycode] = KeyState::IsPressed;
	pressedKeys.push_back(keycode);

	if (keycode == SDLK_ESCAPE)
		GAME.Quit();
}
void InputManager::OnKeyUp(SDL_Keycode keycode) {
	keyStates[keycode] = KeyState::IsReleased;
	releasedKeys.push_back(keycode);
}

bool InputManager::IsKeyPressed(SDL_Keycode keycode) {
	return keyStates[keycode] == KeyState::IsPressed;
}
bool InputManager::IsKeyHeld(SDL_Keycode keycode) {
	return keyStates[keycode] == KeyState::IsHeld;
}
bool InputManager::IsKeyReleased(SDL_Keycode keycode) {
	return keyStates[keycode] == KeyState::IsReleased;
}

bool InputManager::IsMouseHeld()
{
	return isMouseHeld;
}

void InputManager::OnMouseDown() { if (isMouseEventsDisabled) return; isMouseHeld = true; if (onMouseDown) onMouseDown(); }
void InputManager::OnMouseUp() { if (isMouseEventsDisabled) return; isMouseHeld = false; if (onMouseUp) onMouseUp(); }
void InputManager::OnMouseMove() { if (isMouseEventsDisabled) return; if (onMouseMove) onMouseMove(); }