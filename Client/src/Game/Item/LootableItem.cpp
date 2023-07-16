#include "LootableItem.h"
#include "../../UI/UserInterface.h"
#include "../../Managers/UIManager.h"

// Constructor
LootableItem::LootableItem(Item* _item, Vector2 pos): item(_item) {
	// Set Renderer Variables
	renderer.SetPositionRelative();
	renderer.AssignTexture(item->texturePath);

	// Set Transform Position
	transform.SetPosition(pos);

	// Create a beam if the dropped item is an Artifact.
	if (item->rarity == ItemRarity::Artifact) {
		beam = new Beam();
		beam->transform.SetPosition(transform.GetPosition());
	}
}

// Base Functions
void LootableItem::Render() { UIElement::Render(); }

// Main Functions
void LootableItem::Loot() {
	item->OnLoot();
	Delete();
}

// Events
bool LootableItem::OnClick() {
	Loot();
	return isBlockingRaycasts;
}
void LootableItem::OnDelete() {
	// Update the UI Tooltip if we were being hovered on.
	if (UIMgr.currentHoveredElement == this) {
		UIMgr.currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr);
	}

	// If there's a beam associated with this lootable item, delete it.
	if (beam) beam->Delete();

	// Call the item's OnDelete event and also delete it from memory.
	if (!item) return;
	item->OnDelete();
	delete item;
}
void LootableItem::OnMouseEnter() { UI.UpdateTooltip(item); }
void LootableItem::OnMouseOver() {}
void LootableItem::OnMouseLeave() { UI.UpdateTooltip(nullptr); }