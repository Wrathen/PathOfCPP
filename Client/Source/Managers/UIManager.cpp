#include <algorithm>
#include "UIManager.h"
#include "GameManager.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Point.h"
#include "../UI/UserInterface.h"
#include <cassert>

void UIManager::Update() {
	Collection::Update();

	// If the Collection is dirty, which means the list has either some new element added or removed.
	// So we should sort the array to reflect on Z-Indexing.
	auto& allElements = *GetAll();
	if (isDirty) {
		std::sort(allElements.begin(), allElements.end(), [](UIElement* a, UIElement* b) { return a->zIndex > b->zIndex; });
		isDirty = false;
	}

	// For each element in the collection, update and render them.
	for (auto& element : allElements) {
		element->Update();
		if (!element->isAutomaticRenderingDisabled)
			element->Render();
	}

	// Render currently held Item 
	if (currentHeldItem) {
		currentHeldItem->transform.SetPosition(Mouse::GetPosition());
		currentHeldItem->Render();
	}
}

void UIManager::OnMouseMove() {
	// If Power Ups are shown, we shouldn't do any mouseover checks.
	{
		bool powerUpsAreShown = UI.powerUpGroup && UI.powerUpGroup->GetVisible();
		if (powerUpsAreShown) return;
	}

	// If we already have a current hovered element, we should just check it first whether we still hovering over it.
	{
		// [@todo] check whether you could do something about code repetition.
		if (currentHoveredElement) {
			// If the current hovered element is queued for deletion, we should immediately run away! :D
			if (currentHoveredElement->isToBeDeleted) {
				currentHoveredElement = nullptr;
				return;
			}

			// Check whether we still are hovering over the same UIElement.
			Vector2 elementScreenPos = currentHoveredElement->transform.GetScreenPosition();

			// Set variables of the target element.
			unsigned int targetWidth = currentHoveredElement->renderer.width;
			unsigned int targetHeight = currentHoveredElement->renderer.height;
			Rect targetCollider{ (int)elementScreenPos.x, (int)elementScreenPos.y, (int)targetWidth, (int)targetHeight };

			// If it gets offsetted by getting drawn centered, we should offset back.
			if (currentHoveredElement->renderer.shouldDrawCentered) {
				targetCollider.x -= targetWidth / 2;
				targetCollider.y -= targetHeight / 2;
			}

			// Check whether we still are hovering over the same UIElement.
			if (Mouse::GetPosition().ToPoint().Intersects(targetCollider)) {
				currentHoveredElement->OnMouseOver();
				return;
			}

			currentHoveredElement->OnMouseLeave();
			currentHoveredElement = nullptr;
		}
	}

	// Cache variables before the for loop so it's a bit better for performance.
	Point mousePos = Mouse::GetPosition().ToPoint();
	int screenWidth = GAME.screenWidth;
	int screenHeight = GAME.screenHeight;

	// Naive bruteforce O(n) -- Maybe we could use spatial hash here too.
	for (auto& element : *GetAll()) {
		if (!element->isInteractable || element->isToBeDeleted) continue;
		// We can't mouse over to the currently held item.
		if (element == currentHeldItem) continue;

		// Check whether the screen position of the element is within screen bounds.
		Vector2 elementScreenPos = element->transform.GetScreenPosition();
		if (elementScreenPos.x > GAME.screenWidth || elementScreenPos.x < 0 ||
			elementScreenPos.y > GAME.screenHeight || elementScreenPos.y < 0) continue;

		// Set variables of the target element.
		unsigned int targetWidth = element->renderer.width;
		unsigned int targetHeight = element->renderer.height;
		Rect targetCollider{ (int)elementScreenPos.x, (int)elementScreenPos.y, (int)targetWidth, (int)targetHeight };

		// If it gets offsetted by getting drawn centered, we should offset back.
		if (element->renderer.shouldDrawCentered) {
			targetCollider.x -= targetWidth / 2;
			targetCollider.y -= targetHeight / 2;
		}

		// If the mouse position intersects with the target's collider,
		// Select the new UIElement as the current hovered and inform them that the mouse just entered their collider!
		if (mousePos.Intersects(targetCollider)) {
			currentHoveredElement = element;
			currentHoveredElement->OnMouseEnter();
			return;
		}
	}
}
bool UIManager::OnMouseDown() {
	// If we are holding an item in hand, we need to handle the situation differently.
	{
		if (currentHeldItem) {
			// If there is no hovered UI element, just drop the item on ground.
			if (!currentHoveredElement) {
				UI.inventory->Drop(currentHeldItem);
				currentHeldItem = nullptr;
				return true;
			}

			// If we could apply the item onto the hovered UIElement, nullify the held item and return.
			if (currentHoveredElement->canItemsBeApplied && currentHoveredElement->OnApplyItem(currentHeldItem))
				currentHeldItem = nullptr;

			return true;
		}
	}

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
		if (!element || !element->isInteractable || element->isToBeDeleted) continue;
		auto target = element;

		Vector2 targetPos = target->transform.GetScreenPosition();
		auto targetWidth = target->renderer.width;
		auto targetHeight = target->renderer.height;
		Rect targetCollider{ (int)targetPos.x, (int)targetPos.y, (int)targetWidth, (int)targetHeight };

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
void UIManager::PickItemToHand(UIItem* item) {
	// Enforce that we are currently not holding an item.
	assert(currentHeldItem == nullptr);

	// Set the current held item variable to the item and if we were hovering over that item, we shouldn't.
	currentHeldItem = item;
	if (currentHoveredElement == item) {
		currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr, nullptr, TooltipPositionType::NONE);
	}
}