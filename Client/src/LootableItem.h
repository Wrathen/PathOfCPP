#pragma once
#include "UI/UIElement.h"
#include "Miscellaneous/Log.h"

class LootableItem : public UIElement {
public:
	LootableItem();

	void Loot();
	bool OnClick() override;
};