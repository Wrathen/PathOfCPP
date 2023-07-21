#include "Item.h"
#include "LootableItem.h"
#include "../../Miscellaneous/Random.h"
#include "Currency/Currency.h"
#include "Equipment/Equipment.h"

// Static Methods
Item* Item::CreateRandomItem(int itemLevel) {
	// Do some weighted random to choose an itemtype.
	WeightedRandom<int> wr;
	wr.Add(0, 100); // 0.99% chance for Equipments
	wr.Add(1, 10000); // 99.01% chance for Currencies
	ItemType itemType = static_cast<ItemType>(wr.GetRandom());

	// Create an item with the random type and return it.
	if (itemType == ItemType::Equipment) return Equipment::CreateRandomEquipment(itemLevel);
	else if (itemType == ItemType::Currency) return Currency::CreateRandomCurrency(itemLevel);
	return nullptr;
}
void Item::DropItem(int itemLevel, Vector2 pos) {
	LootableItem* loot = new LootableItem(CreateRandomItem(itemLevel), pos);
}