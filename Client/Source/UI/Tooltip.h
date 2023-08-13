#pragma once
#include "UIElement.h"
#include "../Game/Item/UIItem.h"
#include "../Components/TextRenderer.h"

enum class TooltipPositionType {
	NONE = 0,
	LootableItem = 1, // Most-Right of the screen, just above mana bar.
	InventoryItem = 2, // Just above the UIElement.
	EquipmentItem = 3 // Left side of the UIElement.
};

class Tooltip : public UIElement {
	UIElement* targetUIElement = nullptr;
	Item* item = nullptr;
	TextRenderer text_name;
	TextRenderer text_mods;
	TextRenderer text_description;
	SpriteRenderer title;
	
	// UIElements can have different types of positioning on tooltips.
	// i.e. LootableItems (on-ground-items) show on the most-right of the screen.
	// So we define an enum to control these situations.
	TooltipPositionType positionType = TooltipPositionType::NONE;

public:
	Tooltip();

	// Main Functions
	void SetItem(UIElement* target, Item* _item, TooltipPositionType _positionType);
	void ColorizeRainbow();
	void UpdatePosition();
	void ChangeSize(uint32_t newWidth, uint32_t newHeight);

	// Events
	void Start() override;
	void Update() override;
	void Render() override;
	void OnDelete() override {}

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};