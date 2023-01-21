#pragma once
#include "../../UI/UIElement.h"
#include "../../Miscellaneous/Log.h"
#include "Item.h"

class LootableItem : public UIElement {
public:
	Item* item;
	LootableItem(Item* _item);

	void Loot();
	bool OnClick() override;
	void OnDelete() override;
	void OnMouseEnter() override;
	void OnMouseOver() override;
	void OnMouseLeave() override;
};