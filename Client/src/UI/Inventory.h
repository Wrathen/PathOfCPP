#pragma once
#include <vector>
#include "UIElement.h"
#include "../Game/Item/UIItem.h"

class Inventory : public UIElement {
public:
	std::vector<UIItem*> allItems;
	uint32_t cellSizeW = 64;
	uint32_t cellSizeH = 64;
	const uint32_t cellCols = 8; // Number of cells in X axis. Don't think much about X and Y tho :D
	const uint32_t cellRows = 8; // Number of cells in Y axis.
	const uint32_t cellCapacity = cellCols * cellRows;
	
	// Constructor
	Inventory();

	// Main functions
	bool Add(UIItem* item);
	void Drop(UIItem* item);
	void Drop(uint32_t x, uint32_t y);

	// Events
	void Render() override;
	void OnDelete() override {}
	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};