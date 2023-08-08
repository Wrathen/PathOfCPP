#pragma once
#include "../Item.h"
#include "EquipmentStats.h"

enum class EquipmentType {
	Helm = 0,
	Chest = 1,
	Feet = 2,
	Cloak = 3,
	Ring = 4,
	Amulet = 5,
	Count
};

class Equipment: public Item {
public:
	EquipmentType equipmentType;
	EquipmentStats stats;

	// Constructors & Deconstructors
	Equipment();
	Equipment(EquipmentType _equipmentType);

	// Main Functions
	virtual void Equip();
	virtual void Unequip();
	std::string GetName() override;
	std::string GetDescription() override;
	std::string GetModsText() override;

	// Events
	virtual void OnEquip();
	virtual void OnUnequip();
	virtual void OnDelete() override;
	virtual void OnLoot() override;
	virtual void OnUse() override;

	// Static Functions
	static Equipment* CreateRandomEquipment(int itemLevel);
};