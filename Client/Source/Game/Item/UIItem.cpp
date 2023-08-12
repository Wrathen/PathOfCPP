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
	renderer.SetWidth(54);
	renderer.SetHeight(54);
	renderer.shouldDrawCentered = true;
}

// Base Functions
void UIItem::Start() { Super::Start(); }
void UIItem::Update() { Super::Update(); }
void UIItem::Render() { 
	Super::Render();
	GAME.DrawRect(transform.GetScreenPosition().x - renderer.GetWidth()/2,
				  transform.GetScreenPosition().y - renderer.GetHeight()/2,
				  renderer.GetWidth(),
				  renderer.GetHeight(), {127, 127, 127, 127});
}

// Events
bool UIItem::OnClick() {
	UIMgr.PickItemToHand(this);
	return isBlockingRaycasts;
}
void UIItem::OnDelete() {
	// Update the UI Tooltip if we were being hovered on.
	if (UIMgr.currentHoveredElement == this) {
		UIMgr.currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr, nullptr);
	}
}
void UIItem::OnMouseEnter() { UI.UpdateTooltip(this, item); }
void UIItem::OnMouseOver() {}
void UIItem::OnMouseLeave() { UI.UpdateTooltip(nullptr, nullptr); }