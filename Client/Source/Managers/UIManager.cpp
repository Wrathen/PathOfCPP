#include <algorithm>
#include "UIManager.h"
#include "GameManager.h"
#include "../Miscellaneous/ErrorHandler.h"
#include "../UI/UserInterface.h"

void UIManager::Update() {
	// If the Collection is dirty, which means the list has either some new element added or removed.
	// So we should sort the array to reflect on Z-Indexing.
	auto& allElements = GetAll();
	if (isDirty) {
		std::sort(allElements.begin(), allElements.end(), [](std::shared_ptr<UIElement> a, std::shared_ptr<UIElement> b) { return a->zIndex > b->zIndex; });
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
void UIManager::UpdateCollection() { Collection::Update(); }

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
	for (auto& element : GetAll()) {
		if (!element->isInteractable || element->isToBeDeleted) continue;
		// We can't mouse over to the currently held item.
		if (element.get() == currentHeldItem) continue;

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

	// If the power ups are shown, we should only consider power up UI's for mouse clicks.
	if (powerUpsAreShown) {
		auto allShownPowerUps = UI.powerUpGroup->GetCurrentShownPowerUps();
		return HandleMouseDown(allShownPowerUps);
	}

	// Return true or false regarding further raycasting.
	return HandleMouseDown(GetAll());
}
void UIManager::PickItemToHand(UIItem* item) {
	// Enforce that we are currently not holding an item.
	if (currentHeldItem)
		Abort("Picked an item into hand whilst having another one. This exception is not handled.", "Runtime Error");

	// Set the current held item variable to the item and if we were hovering over that item, we shouldn't.
	currentHeldItem = item;
	if (currentHoveredElement.get() == item) {
		currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr, nullptr, TooltipPositionType::NONE);
	}
}