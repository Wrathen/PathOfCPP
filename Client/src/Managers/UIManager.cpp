#include "UIManager.h"
#include "GameManager.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Point.h"
#include "../UI/UserInterface.h"

void UIManager::Update() {
	Collection::Update();

	for (auto& element : *GetAll()) {
		element->Update();
		if (!element->isAutomaticRenderingDisabled)
			element->Render();
	}
}

void UIManager::OnMouseMove() {
	// If Power Ups are shown, we should only check 3 UIElements
	bool powerUpsAreShown = UI.powerUpGroup && UI.powerUpGroup->GetVisible();
	if (powerUpsAreShown) return;

	if (currentHoveredElement && !currentHoveredElement->isToBeDeleted)
		currentHoveredElement->OnMouseOver();

	// Get Mouse Position
	Point mousePos = Mouse::GetPosition().ToPoint();

	int gameWidth = GAME.gameWidth;
	int gameHeight = GAME.gameHeight;

	for (auto& element : *GetAll()) {
		if (!element->isInteractable || element->isToBeDeleted) continue;
		auto elementScreenPos = element->transform.GetScreenPosition();
		if (elementScreenPos.x > gameWidth || elementScreenPos.x < 0 || 
			elementScreenPos.y > gameHeight || elementScreenPos.y < 0) continue;

		auto target = element;
		Vector2 targetPos = elementScreenPos;
		auto targetWidth = target->renderer.width;
		auto targetHeight = target->renderer.height;
		Rect targetCollider{ (int)targetPos.x, (int)targetPos.y, (int)targetWidth, (int)targetHeight };

		// If it gets offsetted by getting drawn centered, we should offset back.
		if (target->renderer.shouldDrawCentered) {
			targetCollider.x -= targetWidth / 2;
			targetCollider.y -= targetHeight / 2;
		}

		if (mousePos.Intersects(targetCollider)) {
			if (currentHoveredElement && !currentHoveredElement->isToBeDeleted) {
				if (element != currentHoveredElement){
					currentHoveredElement->OnMouseLeave();

					currentHoveredElement = element;
					currentHoveredElement->OnMouseEnter();
					return;
				}
			}

			currentHoveredElement = element;
			currentHoveredElement->OnMouseEnter();
			return;
		}
	}

	if (currentHoveredElement && !currentHoveredElement->isToBeDeleted) {
		currentHoveredElement->OnMouseLeave();
		currentHoveredElement = nullptr;
	}
}
bool UIManager::OnMouseDown() {
	// If Power Ups are shown, we should only check 3 UIElements
	bool powerUpsAreShown = UI.powerUpGroup && UI.powerUpGroup->GetVisible();

	// If we are already hovering over an element, just click it
	if (!powerUpsAreShown && currentHoveredElement && !currentHoveredElement->isToBeDeleted)
		return currentHoveredElement->OnClick();

	// Get Mouse Position
	Point mousePos = Mouse::GetPosition().ToPoint();

	// Get The List of Elements we are going to check
	auto elementVector = 
		powerUpsAreShown ? UI.powerUpGroup->GetCurrentShownPowerUps() : *GetAll();

	// Iterate over all viable elements and send them the OnClick event.
	for (auto& element : elementVector) {
		if (!element || !element->isInteractable) continue;
		auto target = element;

		Vector2 targetPos = target->transform.GetScreenPosition();
		auto targetWidth = target->renderer.width;
		auto targetHeight = target->renderer.height;
		Rect targetCollider{ (int)targetPos.x, (int)targetPos.y, (int)targetWidth, (int)targetHeight};
		
		// If it gets offsetted by getting drawn centered, we should offset back.
		if (target->renderer.shouldDrawCentered) {
			targetCollider.x -= targetWidth / 2;
			targetCollider.y -= targetHeight / 2;
		}

		if (mousePos.Intersects(targetCollider)) {
			bool raycastBlocked = target->OnClick();
			if (raycastBlocked) return true;
		}
	}

	// Return false, indicating further raycasts are not blocked.
	return false;
}