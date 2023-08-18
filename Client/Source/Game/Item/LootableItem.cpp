#include "LootableItem.h"
#include "../../UI/UserInterface.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/GameManager.h"

// Constructor
LootableItem::LootableItem(Item* _item, Vector2 pos) : item(_item) {
	// Set interactability to true. So we can hover over & click on dropped items.
	isInteractable = true;

	// Set Renderer Variables
	renderer.SetPositionRelative();
	renderer.AssignTexture(item->texturePath);
	renderer.shouldDrawCentered = true;

	// Set Transform Position
	transform.SetPosition(pos);

	// Create a beam if the dropped item is an Artifact.
	if (item->rarity == ItemRarity::Artifact) {
		beam = new Beam();
		beam->transform.SetPosition(transform.GetPosition());
	}
}

// Base Functions
void LootableItem::Update() {
	Super::Update();
	static bool isPlayerNearby = false;

	if (item && item->type == ItemType::Currency) {
		float distanceToPlayer = Vector2::DistanceBetweenFast(GAME.GetPlayer()->transform.GetPosition(), transform.GetPosition());
		if (!isPlayerNearby && distanceToPlayer < 80) {
			isPlayerNearby = true;
			OnPlayerNearby();
		}
		else if (isPlayerNearby && distanceToPlayer > 80) {
			isPlayerNearby = false;
			OnPlayerAway();
		}
	}
}
void LootableItem::Render() { Super::Render(); }

// Main Functions
void LootableItem::Loot() {
	// Check if the item is a valid object
	if (item) {
		// Call the OnLoot event on the item.
		item->OnLoot();

		// We add only the equipment items into our inventory.
		if (item->type == ItemType::Equipment) {
			// Put the item into Inventory.
			UIItem* inventoryItem = new UIItem(item);
			bool success = UI.inventory->Add(inventoryItem);

			// If there was an error, i.e. no space available in inventory, delete the UIItem.
			if (!success) {
				inventoryItem->Delete();
				return;
			}

			// We set the item pointer to null because
			// in the OnDelete() function, we also delete the item.
			// But, if we successfully put the item into our inventory,
			// we shouldn't delete the item, right? So this is a cheesy way! ^^
			item = nullptr;
		}
	}

	// We just want to delete this LootableItem object.
	Delete();
}

// Events
void LootableItem::OnPlayerNearby() { Loot(); }
void LootableItem::OnPlayerAway() { }
bool LootableItem::OnClick() {
	Loot();
	return isBlockingRaycasts;
}
void LootableItem::OnDelete() {
	// Update the UI Tooltip if we were being hovered on.
	if (UIMgr.currentHoveredElement == this) {
		UIMgr.currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr, nullptr, TooltipPositionType::NONE);
	}

	// If there's a beam associated with this lootable item, delete it.
	if (beam) beam->Delete();

	// Call the item's OnDelete event and also delete it from memory.
	if (!item) return;
	item->OnDelete();
	delete item;
	item = nullptr;
}
void LootableItem::OnMouseEnter() { UI.UpdateTooltip(this, item, TooltipPositionType::LootableItem); }
void LootableItem::OnMouseOver() {}
void LootableItem::OnMouseLeave() { UI.UpdateTooltip(nullptr, nullptr, TooltipPositionType::NONE); }