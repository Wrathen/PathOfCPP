#include "Equipment.h"
#include "../../../Miscellaneous/Random.h"
#include "EquipmentTexturePaths.h"
#include <vector>

static std::string namePrefixes[] = {
	"Superior",
	"Gladiator's",
	"Devilish",
	"Gigantic",
	"Foolish",
	"Warrior's",
	"Demonic",
	"Satanic",
	"Ruthless",
	"Hardened",
	"Vampiric",
	"Sadistic",
	"Vengeful",
	"Archmage's",
	"Soothed",
	"Wealthy",
	"Blessed",
	"Thundering",
	"Thunderfury"
};
static std::string names[] = {
	"Helm",
	"Chest",
	"Feet",
	"Cloak",
	"Ring",
	"Amulet"
};
static std::string nameAffixes[] = {
	"of the Damned",
	"of the Banished",
	"of the Boar",
	"of the Forbidden",
	"of Firelashed",
	"of the Singing Rocks",
	"of the Sanguine",
	"of the Elementals",
	"of Storms",
	"of the Windseeker",
	"of the Thunder",
	"of the Night",
	"the Nightbreaker",
	"the Nightbringer",
	"of the Night",
	"of the Light",
	"the Lightbreaker",
	"the Lightbringer",
	"the Crusher",
	"the Demolisher",
	"the Light of Dawn",
	"of Hell-Sight",
	"the Godslayer",
	"of the Godslayer"
};

// Constructors & Deconstructors
Equipment::Equipment() { type = ItemType::Equipment; equipmentType = EquipmentType::Count; }
Equipment::Equipment(EquipmentType _equipmentType) : Equipment() {
	// Will notify me that I need to change here when I add more types.
	static_assert((int)EquipmentType::Count == 6);

	equipmentType = _equipmentType;
	texturePath = equipmentType == EquipmentType::Helm ? GetRandomTexturePath_Helm() :
		equipmentType == EquipmentType::Chest ? GetRandomTexturePath_Chest() :
		equipmentType == EquipmentType::Feet ? GetRandomTexturePath_Feet() :
		equipmentType == EquipmentType::Cloak ? GetRandomTexturePath_Cloak() :
		equipmentType == EquipmentType::Ring ? GetRandomTexturePath_Ring() :
		equipmentType == EquipmentType::Amulet ? GetRandomTexturePath_Amulet() : "";

	bool containsPrefix = RandomInt(0, 100) > 80;
	bool containsAffix = RandomInt(0, 100) > 40;
	name = (containsPrefix ? namePrefixes[RandomInt(0, 19)] + " " : "") +
		names[(int)equipmentType] + (containsAffix ? " " + nameAffixes[RandomInt(0, 24)] : "");
}

// Static Functions
Equipment* Equipment::CreateRandomEquipment(int itemLevel) {
	EquipmentType equipmentType = RandomEnum(EquipmentType::Count);
	ItemRarity itemRarity = RandomEnum(ItemRarity::Count);
	Equipment* equipment = new Equipment(equipmentType);
	equipment->equipmentType = equipmentType;
	equipment->itemLevel = (float)itemLevel;
	equipment->rarity = itemRarity;
	equipment->description = itemRarity == ItemRarity::Magic ? "Magical it seems, yet so weak." :
		itemRarity == ItemRarity::Rare ? "Seeking more, MORE!" :
		itemRarity == ItemRarity::Legendary ? "Wow! This might be one of\n it's kind." :
		itemRarity == ItemRarity::Artifact ? "Still sane exile?" : "A worthy equipment for the filthy.";

	equipment->stats.Randomize((float)itemLevel, (int)itemRarity, (int)itemRarity, ((int)itemRarity * 0.67f) + 1.0f);

	return equipment;
}

// Main Functions
void Equipment::Equip() {
	OnEquip();
}
void Equipment::Unequip() {
	OnUnequip();
}

std::string Equipment::GetName() { return name; }
std::string Equipment::GetDescription() { return description; }
std::string Equipment::GetModsText() { // @todo fix below garbage code.
	std::string text;
	auto& prefixes = stats.GetPrefixes();
	auto& suffixes = stats.GetSuffixes();

	for (auto& prefix : prefixes) {
		// Replace $ with a new line.
		std::string format = prefix.db.Format;
		auto dollarInd = format.find("$");
		if (dollarInd != -1) {
			format.replace(dollarInd, 1, "\n");
		}

		// Replace #'s with modifier values.
		auto ind = format.find('#');
		std::string coef = std::to_string((int)prefix.coefValue1);
		format.replace(ind, 1, coef);
		if (prefix.coefValue2 != 0) {
			ind = format.find('#');
			coef = std::to_string((int)prefix.coefValue2);
			format.replace(ind, 1, coef);
		}
		if (prefix.coefValue3 != 0) {
			ind = format.find('#');
			coef = std::to_string((int)prefix.coefValue3);
			format.replace(ind, 1, coef);
		}

		// Finally, add the formatted modifier text into the output text.
		text += format + "\n";
	}
	for (auto& suffix : suffixes) {
		// Replace $ with a new line.
		std::string format = suffix.db.Format;
		auto dollarInd = format.find("$");
		if (dollarInd != -1) {
			format.replace(dollarInd, 1, "\n");
		}

		// Replace #'s with modifier values.
		auto ind = format.find('#');
		std::string coef = std::to_string((int)suffix.coefValue1);
		format.replace(ind, 1, coef);
		if (suffix.coefValue2 != 0) {
			ind = format.find('#');
			coef = std::to_string((int)suffix.coefValue2);
			format.replace(ind, 1, coef);
		}
		if (suffix.coefValue3 != 0) {
			ind = format.find('#');
			coef = std::to_string((int)suffix.coefValue3);
			format.replace(ind, 1, coef);
		}

		// Finally, add the formatted modifier text into the output text.
		text += format + "\n";
	}

	return text;
}

// Events
void Equipment::OnEquip() { isEquipped = true; }
void Equipment::OnUnequip() { isEquipped = false; }
void Equipment::OnDelete() {}
void Equipment::OnLoot() {}
void Equipment::OnUse() {}