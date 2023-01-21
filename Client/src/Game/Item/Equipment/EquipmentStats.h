#pragma once
#include <vector>
#include "../../../Miscellaneous/Random.h"
#include "EquipmentTexturePaths.h"

enum class ItemModifierType {
	Strength,
	Agility,
	Intellect,
	MaxHP,
	Crit,
	Haste,
	Mastery,
	Versatility,
	Count
};
struct ItemModifier {
	ItemModifierType type;
	std::string name;
	float value;
};
static ItemModifier all_prefixes[] = {
	ItemModifier{ItemModifierType::Strength, "+# to Strength", 0.0f},
	ItemModifier{ItemModifierType::Agility, "+# to Agility", 0.0f},
	ItemModifier{ItemModifierType::Intellect, "+# to Intellect", 0.0f},
	ItemModifier{ItemModifierType::MaxHP, "+# to Maximum Life", 0.0f}
};
static ItemModifier all_suffixes[] = {
	ItemModifier{ItemModifierType::Crit, "+#% Increased Crit Chance", 0.0f},
	ItemModifier{ItemModifierType::Haste, "+#% Haste", 0.0f},
	ItemModifier{ItemModifierType::Mastery, "+#% Mastery", 0.0f},
	ItemModifier{ItemModifierType::Versatility, "+#% Versatility", 0.0f}
};

class EquipmentStats {
private:
	std::vector<ItemModifier> prefixes;
	std::vector<ItemModifier> suffixes;

public:
	EquipmentStats() {}

	void Randomize(float itemLevel, int prefixCount, int suffixCount, float multiplier) {
		for (int i = 0; i < prefixCount; ++i) {
			ItemModifier stat = all_prefixes[RandomInt(4)];
			bool statAlreadyExists = false;

			for (int j = 0; j < prefixes.size(); ++j) {
				if (prefixes[j].type == stat.type) {
					statAlreadyExists = true;
					prefixes[j].value += itemLevel * multiplier;
					break;
				}
			}

			if (!statAlreadyExists) {
				stat.value += itemLevel * multiplier;
				prefixes.insert(prefixes.end(), stat);
			}
		}
		for (int i = 0; i < suffixCount; ++i) {
			ItemModifier stat = all_suffixes[RandomInt(4)];
			bool statAlreadyExists = false;

			for (int j = 0; j < suffixes.size(); ++j) {
				if (suffixes[j].type == stat.type) {
					statAlreadyExists = true;
					suffixes[j].value += itemLevel * multiplier;
					return;
				}
			}

			if (!statAlreadyExists) {
				stat.value += itemLevel * multiplier;
				suffixes.insert(suffixes.end(), stat);
			}
		}
	}
	
	int GetPrefixAmount() const { return prefixes.size(); }
	int GetSuffixAmount() const { return suffixes.size(); }
	const auto& GetPrefix(int number) const { return prefixes[number]; }
	const auto& GetSuffix(int number) const { return suffixes[number]; }
	const auto& GetPrefixes() const { return prefixes; }
	const auto& GetSuffixes() const { return suffixes; }
};