#include "Inventory.h"
#include "Miscellaneous/Log.h"
#include "Managers/GameManager.h"
#include "Managers/UIManager.h"

Inventory::Inventory() : UIElement("Assets/Sprites/UI/Inventory/background.png") {
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

	// Get the smart pointer of the item
	std::shared_ptr<UIElement> itemBasePTR = UIMgr.Get(item->guid);
	std::shared_ptr<UIItem> itemPTR = std::static_pointer_cast<UIItem>(itemBasePTR);

	// If the item shared pointer was not found in UIManager's collection, what the heck?!
	if (!itemPTR) 
		return false;

	// Pick an empty space as <row, col>.
	uint32_t row = emptySlot % cellCols;
	uint32_t col = emptySlot / cellCols;
	
	// Sorry for hardcoding, I'm just trying to offset the coordinates to the inventory space within the image.
	static float offsetX = GAME.screenWidth - renderer.width + 45;
	static float offsetY = 638;

	// Free up the space from the OccupiedSpaceFlag so we can place items there next time.
	inventoryOccupiedSpaceFlag = ((1ull << emptySlot) | inventoryOccupiedSpaceFlag);

	// Set the position of the item and push it into the vector.
	item->transform.SetPosition(Vector2(row * cellSizeW + offsetX, col * cellSizeH + offsetY));
	allItems[emptySlot] = itemPTR;

	// We successfully added the UIItem to the inventory.
	return true;
}

void Inventory::Drop(uint32_t x, uint32_t y) { Drop(x + y * cellCols); }
void Inventory::Drop(UIItem* item) { for (size_t i = 0; i < cellCapacity; ++i) if (allItems[i].get() == item) Drop(i); return; }
void Inventory::Drop(uint32_t slotIndex) {
	// Get the item by slotIndex.
	std::shared_ptr<UIItem> item = allItems[slotIndex];
	if (!item) return;

	// Free up the space from the OccupiedSpaceFlag so we can place items there next time.
	inventoryOccupiedSpaceFlag &= ~(1ull << slotIndex);

	// Delete from the array and free the memory.
	allItems[slotIndex] = nullptr;

	// Drop the item
	Item::DropItem(item->item, GAME.GetPlayer()->transform.GetPosition());
	item->Delete();
}
void Inventory::Remove(uint32_t x, uint32_t y) { Remove(x + y * cellCols); }
void Inventory::Remove(UIItem* item) { for (size_t i = 0; i < cellCapacity; ++i) if (allItems[i].get() == item) Remove(i); return; }
void Inventory::Remove(uint32_t slotIndex) {
	// Get the item by slotIndex.
	std::shared_ptr<UIItem>& item = allItems[slotIndex];
	if (!item) return;

	// Free up the space from the OccupiedSpaceFlag so we can place items there next time.
	inventoryOccupiedSpaceFlag &= ~(1ull << slotIndex);

	// Delete from the array and free the memory.
	allItems[slotIndex] = nullptr;
}

void Inventory::Render() {
	Super::Render();
	for (std::shared_ptr<UIItem>& item: allItems)
		if (item) item->Render();
}

void Inventory::SetVisible(bool flag) {
	Super::SetVisible(flag);

	// Change state of all items' interactability and visibility based on the flag.
	for (std::shared_ptr<UIItem>& item : allItems) {
		if (!item) continue;
		item->SetVisible(flag);
		item->SetInteractable(flag);
	}
}

// naive bruteforce approach O(n) --> @todo improve this.
uint32_t Inventory::FindEmptySlot() {
	for (size_t i = 0; i < cellCapacity; ++i)
		if (!(inventoryOccupiedSpaceFlag & (1ull << i))) 
			return i;

	return cellCapacity + 1;
}