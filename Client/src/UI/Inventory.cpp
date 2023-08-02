#include "Inventory.h"
#include "../Miscellaneous/Log.h"
#include "../Managers/GameManager.h"

Inventory::Inventory() : UIElement(/*"assets/sprites/UI/powerup/background.png"*/) {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	isBlockingRaycasts = false;
	isInteractable = false;

	allItems.reserve(cellCapacity);

	SetVisible(false);
}

bool Inventory::Add(UIItem* item) {
	uint32_t numberOfItems = allItems.size();
	uint32_t col = numberOfItems % cellCols;
	uint32_t row = numberOfItems / cellRows;
	
	// Out of capacity!
	if (numberOfItems + 1 > cellCapacity) return false;

	static int offsetX = 32;
	static int offsetY = 32;

	// Set the position of the item and push it into the vector.
	item->transform.SetPosition(Vector2(col * cellSizeW + offsetX, row * cellSizeH + offsetY));
	allItems.push_back(item);

	// We successfully added the UIItem to the inventory.
	return true;
}

void Inventory::Drop(uint32_t x, uint32_t y) { if (UIItem* itemToDrop = allItems[x + y * cellCols]) Drop(itemToDrop); }
void Inventory::Drop(UIItem* item) {
	// Find the item in the array
	auto position = std::find(allItems.begin(), allItems.end(), item);
    if (position == allItems.end()) {
        Warn("The item was not found in the Inventory, why do you call Inventory::Remove(_) ?");
        Warn(item->ToString());
        return;
    }
	
	// Drop the item
	Item::DropItem(item->item, GAME.GetPlayer()->transform.GetPosition());

	// Delete from the array and free the memory.
    allItems.erase(position);
	item->OnDelete();
    delete item;
}

void Inventory::Render() {
	Super::Render();
	for (UIItem* item: allItems)
		item->Render();
}