#pragma once
#include "../../Miscellaneous/Vector.h"

enum class ItemRarity {
	Common = 0,
	Magic = 1,
	Rare = 2,
	Legendary = 3,
	Artifact = 4,
	Count
};
enum class ItemType {
	Equipment = 0,
	Currency = 1,
	Count
};

class Item {
public:
	// Members
	ItemType type;
	ItemRarity rarity;
	std::string name;
	std::string description;
	std::string texturePath;
	float itemLevel = 1;

	// Main Methods
	virtual std::string GetName() = 0;
	virtual std::string GetDescription() = 0;
	virtual std::string GetModsText() = 0;

	// Static Methods
	static Item* CreateRandomItem(int itemLevel);
	static void DropItem(int itemLevel, Vector2 pos);

	// Events
	// Called when the pointer gets deleted
	virtual void OnDelete() {};
	// Called when looted from ground
	virtual void OnLoot() = 0;
	// Called when used
	virtual void OnUse() {};
};