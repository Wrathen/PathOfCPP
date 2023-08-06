#include "Inventory.h"
#include "../Miscellaneous/Log.h"
#include "../Managers/GameManager.h"

Inventory::Inventory() : UIElement("assets/sprites/UI/inventory/background.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	isBlockingRaycasts = false;
	isInteractable = false;

	// Initialize allItems array.
	allItems.reserve(cellCapacity);
	for (size_t i = 0; i < cellCapacity; ++i)
		allItems.push_back(nullptr);

	// Set the initial visibility to false. We can show/hide Inventory by pressing <B>.
	SetVisible(false);

	// Set the background width&height to encapsulate the whole inventory cells.
	renderer.SetColor({ 255, 255, 255, 255 });
	transform.SetPosition(GAME.screenWidth - renderer.GetWidth(),
						  GAME.screenHeight - renderer.GetHeight());
}

// [@todo] this sux.
bool Inventory::Add(UIItem* item) {
	uint32_t emptySlot = FindEmptySlot();
	
	// No empty slot was found in the inventory. Out of capacity!
	if (emptySlot > cellCapacity)
		return false;

	// Pick an empty space as <row, col>.
	uint32_t row = emptySlot % cellCols;
	uint32_t col = emptySlot / cellCols;
	
	// Sorry for hardcoding, I'm just trying to offset the coordinates to the inventory space within the image.
	static float offsetX = GAME.screenWidth - renderer.width + 45;
	static float offsetY = 638;

	// Set the position of the item and push it into the vector.
	item->transform.SetPosition(Vector2(row * cellSizeW + offsetX, col * cellSizeH + offsetY));
	allItems[emptySlot] = item;

	// We successfully added the UIItem to the inventory.
	return true;
}

void Inventory::Drop(uint32_t x, uint32_t y) { Drop(x + y * cellCols); }
void Inventory::Drop(UIItem* item) { for (size_t i = 0; i < cellCapacity; ++i) if (allItems[i] == item) Drop(i); return; }
void Inventory::Drop(uint32_t slotIndex) {
	// Get the item by slotIndex.
	UIItem* item = allItems[slotIndex];
	if (!item) return;

	// Delete from the array and free the memory.
	allItems[slotIndex] = nullptr;

	// Drop the item
	Item::DropItem(item->item, GAME.GetPlayer()->transform.GetPosition());
	item->Delete();
}
void Inventory::Remove(uint32_t x, uint32_t y) { Remove(x + y * cellCols); }
void Inventory::Remove(UIItem* item) { for (size_t i = 0; i < cellCapacity; ++i) if (allItems[i] == item) Remove(i); return; }
void Inventory::Remove(uint32_t slotIndex) {
	// Get the item by slotIndex.
	UIItem* item = allItems[slotIndex];
	if (!item) return;

	// Delete from the array and free the memory.
	allItems[slotIndex] = nullptr;
}

void Inventory::Render() {
	Super::Render();
	for (UIItem* item: allItems)
		if (item) item->Render();
}

void Inventory::SetVisible(bool flag) {
	Super::SetVisible(flag);

	// Change state of all items' interactability and visibility based on the flag.
	for (UIItem* item : allItems) {
		if (!item) continue;
		item->SetVisible(flag);
		item->SetInteractable(flag);
	}
}

// naive bruteforce approach O(n) --> @todo improve this.
uint32_t Inventory::FindEmptySlot() {
	for (size_t i = 0; i < cellCapacity; ++i)
		if (!allItems[i]) return i;

	return cellCapacity + 1;
}