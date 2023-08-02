#include "Inventory.h"
#include "../Miscellaneous/Log.h"
#include "../Managers/GameManager.h"

Inventory::Inventory() : UIElement("assets/sprites/UI/powerup/background.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	isBlockingRaycasts = false;
	isInteractable = false;

	allItems.reserve(cellCapacity);

	SetVisible(false);

	// Set the background width&height to encapsulate the whole inventory cells.
	renderer.SetColor({ 255, 255, 255, 70 });
	renderer.SetWidth(cellSizeW * cellCols);
	renderer.SetHeight(cellSizeH * cellRows);
	transform.SetPosition(GAME.screenWidth - (cellSizeW * cellCols), 
						  GAME.screenHeight - (cellSizeH * cellRows));
}

bool Inventory::Add(UIItem* item) {
	uint32_t numberOfItems = allItems.size();
	uint32_t col = numberOfItems % cellCols;
	uint32_t row = numberOfItems / cellRows;
	
	// Out of capacity!
	if (numberOfItems + 1 > cellCapacity) return false;

	static int marginX = 32;
	static int marginY = 32;
	static int offsetX = GAME.screenWidth - (cellSizeW * cellCols);
	static int offsetY = GAME.screenHeight - (cellSizeH * cellRows);
	
	// Set the position of the item and push it into the vector.
	item->transform.SetPosition(Vector2(col * cellSizeW + marginX + offsetX, row * cellSizeH + marginY + offsetY));
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
	item->Delete();
}

void Inventory::Render() {
	Super::Render();
	for (UIItem* item: allItems)
		item->Render();
}

void Inventory::SetVisible(bool flag) {
	Super::SetVisible(flag);

	// Change state of all items' interactability and visibility based on the flag.
	for (UIItem* item : allItems) {
		item->SetVisible(flag);
		item->SetInteractable(flag);
	}
}