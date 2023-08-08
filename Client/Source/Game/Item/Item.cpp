#include "Item.h"
#include "LootableItem.h"
#include "../../Miscellaneous/Random.h"
#include "Currency/Currency.h"
#include "Equipment/Equipment.h"

// Static Methods
Item* Item::CreateRandomItem(int itemLevel, unsigned int seed) {
	// Set the specified seed to the Random Class so it can generate
	// the same item when given the same seed ever again in the future.
	Random::SetSeed(seed);

	// Do some weighted random to choose an itemtype.
	WeightedRandom<int> wr ({0, 1}, {100, 10000});
	//wr.Add(0, 100); // 0.99% chance for Equipments
	//wr.Add(1, 10000); // 99.01% chance for Currencies
	ItemType itemType = static_cast<ItemType>(wr.GetRandom());

	// Create an item with the random type and return it.
	if (itemType == ItemType::Equipment) return Equipment::CreateRandomEquipment(itemLevel);
	else if (itemType == ItemType::Currency) return Currency::CreateRandomCurrency(itemLevel);
	return nullptr;
}

void Item::DropItem(Item* item, Vector2 pos) {
	new LootableItem(item, pos);
}

void Item::DropItem(int itemLevel, Vector2 pos, unsigned int seed) {
	new LootableItem(CreateRandomItem(itemLevel, seed), pos);
}