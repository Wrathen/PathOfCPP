#pragma once
#include <vector>
#include "../../../Miscellaneous/Random.h"
#include "EquipmentTexturePaths.h"
#include "../../../Database/Item/ItemModifier.h"

enum class ItemModifierType {
	IncArmour = 1,
	IncArmour_IncSBR,
	FlatArmour,
	FlatArmour_FlatMaxLife,
	FlatMaxLife,
	PhysReflectToMeleeAttackers,
	AdditionalPhysReduction,
	IncSBR,
	ReducedAttributeRequirements,
	FlatStrength,
	FlatFireResistance,
	FlatLightningResistance,
	FlatColdResistance,
	FlatChaosResistance,
	FlatLifeRegen,
	IncEvasion,
	IncEvasion_IncSBR,
	FlatEvasion,
	FlatEvasion_FlatMaxLife,
	FlatDexterity,
	FlatChanceToSuppressSpellDamage,
	IncEnergyShield,
	IncEnergyShield_IncSBR,
	FlatMaxEnergyShield,
	FlatMaxEnergyShield_FlatMaxLife,
	FlatMaxEnergyShield_FlatMaxMana,
	FlatMaxMana,
	FlatFasterStartOfEnergyShieldRecharge,
	FlatIntelligence,
	IncArmourEvasion,
	IncArmourEvasion_IncSBR,
	FlatArmour_FlatEvasion,
	IncArmourEnergyShield,
	IncArmourEnergyShield_IncSBR,
	FlatArmour_FlatMaxEnergyShield,
	IncEvasionEnergyShield,
	IncEvasionEnergyShield_IncSBR,
	FlatEvasion_FlatMaxEnergyShield,
	IncArmourEvasionEnergyShield,
	IncArmourEvasionEnergyShield_IncSBR,
	Count
};
struct ItemModifier {
	Database::ItemModifier db;
	float coefValue1 = 0;
	float coefValue2 = 0;
	float coefValue3 = 0;

	ItemModifier(Database::ItemModifier dbItemMod) {
		db = dbItemMod;
		coefValue1 = RandomFloat(dbItemMod.CoefMinValue1, dbItemMod.CoefMaxValue1);
		if (dbItemMod.CoefMinValue2 != 0 && dbItemMod.CoefMaxValue2 != 0)
			coefValue2 = RandomFloat(dbItemMod.CoefMinValue2, dbItemMod.CoefMaxValue2);
		if (dbItemMod.CoefMinValue3 != 0 && dbItemMod.CoefMaxValue3 != 0)
			coefValue3 = RandomFloat(dbItemMod.CoefMinValue3, dbItemMod.CoefMaxValue3);
	}
};

class EquipmentStats {
private:
	std::vector<ItemModifier> prefixes;
	std::vector<ItemModifier> suffixes;

public:
	EquipmentStats() {}

	void Randomize(float itemLevel, int prefixCount, int suffixCount, float multiplier) {
		std::vector<Database::ItemModifier> allPrefixes = Database::GetAllItemModifiers(Database::ItemModPoolTypes::BodyArmourSTR, (uint32_t)itemLevel, 2);
		std::vector<Database::ItemModifier> allSuffixes = Database::GetAllItemModifiers(Database::ItemModPoolTypes::BodyArmourSTR, (uint32_t)itemLevel, 0);

		auto randomPrefixes = Database::GetRandomItemModifiers(allPrefixes, prefixCount);
		auto randomSuffixes = Database::GetRandomItemModifiers(allSuffixes, suffixCount);
		
		for (size_t i = 0; i < randomPrefixes.size(); ++i)
			prefixes.emplace_back(ItemModifier(randomPrefixes[i]));
		for (size_t i = 0; i < randomSuffixes.size(); ++i)
			suffixes.emplace_back(ItemModifier(randomSuffixes[i]));
	}
	
	int GetPrefixAmount() const { return prefixes.size(); }
	int GetSuffixAmount() const { return suffixes.size(); }
	const auto& GetPrefix(int number) const { return prefixes[number]; }
	const auto& GetSuffix(int number) const { return suffixes[number]; }
	const auto& GetPrefixes() const { return prefixes; }
	const auto& GetSuffixes() const { return suffixes; }
};