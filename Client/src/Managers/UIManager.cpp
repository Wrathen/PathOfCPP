#include "UIManager.h"
#include "GameManager.h"
#include "../Miscellaneous/Mouse.h"

void UIManager::Update() {
	Collection::Update();

	for (auto& element : *GetAll()) {
		element->Update();
		if (!element->isAutomaticRenderingDisabled)
			element->Render();
	}
}

void UIManager::OnMouseMove() {
	if (currentHoveredElement)
		currentHoveredElement->OnMouseOver();

	Vector2 mousePos = Mouse::GetPosition();
	int gameWidth = GAME.gameWidth;
	int gameHeight = GAME.gameHeight;

	for (auto& element : *GetAll()) {
		if (!element->isInteractable || element->isToBeDeleted) continue;
		auto elementScreenPos = element->transform.GetScreenPosition();
		if (elementScreenPos.x > gameWidth || elementScreenPos.x < 0 || 
			elementScreenPos.y > gameHeight || elementScreenPos.y < 0) continue;

		Vector2 targetPos = element->transform.GetScreenPosition();
		auto targetWidth = element->renderer.width;
		auto targetHeight = element->renderer.height;

		bool collides = mousePos.x > targetPos.x && mousePos.x < targetPos.x + targetWidth &&
			mousePos.y > targetPos.y && mousePos.y < targetPos.y + targetHeight;

		if (collides) {
			if (currentHoveredElement) {
				if (element != currentHoveredElement){
					currentHoveredElement->OnMouseLeave();
					element->OnMouseEnter();
					return;
				}
			}

			currentHoveredElement = element;
			currentHoveredElement->OnMouseEnter();
			return;
		}
	}

	if (currentHoveredElement) {
		currentHoveredElement->OnMouseLeave();
		currentHoveredElement = nullptr;
	}
}
bool UIManager::OnMouseDown() {
	if (currentHoveredElement)
		return currentHoveredElement->OnClick();

	Vector2 mousePos = Mouse::GetPosition();

	for (auto& element : *GetAll()) {
		if (!element->isInteractable) continue;
		auto target = element;

		Vector2 targetPos = target->transform.GetScreenPosition();
		auto targetWidth = target->renderer.width;
		auto targetHeight = target->renderer.height;

		bool collides = mousePos.x > targetPos.x && mousePos.x < targetPos.x + targetWidth &&
			mousePos.y > targetPos.y && mousePos.y < targetPos.y + targetHeight;
		
		if (collides) {
			bool raycastBlocked = target->OnClick();
			if (raycastBlocked) return true;
		}
	}

	return false;
}