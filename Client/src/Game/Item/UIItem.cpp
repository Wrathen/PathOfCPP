#include "UIItem.h"
#include "../../UI/UserInterface.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/GameManager.h"

// Constructor
UIItem::UIItem(Item* _item): item(_item) { 
	// Disable automatic rendering that renders all the UIElements on tick.
	isAutomaticRenderingDisabled = true;

	// Make this object be persistent through scene changes.
	isToBeDeletedOnSceneChange = false;

	// Set interactability to true. So we can hover over & click on dropped items.
	isInteractable = true;

	// Set Renderer Variables
	renderer.SetPositionAbsolute();
	renderer.AssignTexture(item->texturePath);
	renderer.shouldDrawCentered = true;
}

// Base Functions
void UIItem::Start() { Super::Start(); }
void UIItem::Update() { Super::Update(); }
void UIItem::Render() { Super::Render(); }

// Events
bool UIItem::OnClick() { 
	UI.inventory->Drop(this);
	return isBlockingRaycasts;
}
void UIItem::OnDelete() {
	// Update the UI Tooltip if we were being hovered on.
	if (UIMgr.currentHoveredElement == this) {
		UIMgr.currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr);
	}
}
void UIItem::OnMouseEnter() { UI.UpdateTooltip(item); }
void UIItem::OnMouseOver() {}
void UIItem::OnMouseLeave() { UI.UpdateTooltip(nullptr); }