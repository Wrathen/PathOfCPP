#pragma once
#include <vector>
#include <memory>
#include "UIElement.h"
#include "../Game/Item/UIItem.h"

class Inventory : public UIElement {
public:
	std::vector<std::shared_ptr<UIItem>> allItems;
	uint32_t cellSizeW = 54;
	uint32_t cellSizeH = 54;
	const uint32_t cellCols = 12; // Number of cells in X axis. Don't think much about X and Y tho :D
	const uint32_t cellRows = 5; // Number of cells in Y axis.
	const uint32_t cellCapacity = cellCols * cellRows; // Make sure its not above 63 though. Cuz of below.
	
	// We have 60 spaces in our inventory, 60 possible open spaces. So we can use a 64 bit integer
	// to represent empty spaces. Should be faster. No, I don't want to manually track the last open position. That is boring.
	// But I have to admit that would be way faster, but whelp, we don't need it yet.
	uint64_t inventoryOccupiedSpaceFlag = 0;

	// Constructor
	Inventory();

	// Main functions
	// Adds an item into the Inventory.
	bool Add(UIItem* item);
	// Drops an item into the ground directly.
	void Drop(UIItem* item);
	void Drop(uint32_t x, uint32_t y);
	void Drop(uint32_t slotIndex);
	// Removes an item from the Inventory. Does NOT delete the UIItem, only removes it from the vector.
	void Remove(UIItem* item);
	void Remove(uint32_t x, uint32_t y);
	void Remove(uint32_t slotIndex);
	void SetVisible(bool flag) override;

	// Events
	void Render() override;
	void OnDelete() override {}
	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}

private:
	uint32_t FindEmptySlot();
};