#pragma once
#include "../../UI/UIElement.h"
#include "../../Miscellaneous/Log.h"
#include "../../Entities/Beam/Beam.h"
#include "Item.h"

class LootableItem : public UIElement {
public:
	// Dropped item.
	Item* item = nullptr;
	// Beam is a VFX created if the dropped item is an Artifact rarity.
	Beam* beam = nullptr;

	// Constructor
	LootableItem(Item* _item, Vector2 pos);
	
	// Base Functions
	void Update() override;
	void Render() override;

	// Main Functions
	void Loot();

	// Events
	void OnPlayerNearby();
	void OnPlayerAway();
	bool OnClick() override;
	void OnDelete() override;
	void OnMouseEnter() override;
	void OnMouseOver() override;
	void OnMouseLeave() override;
};