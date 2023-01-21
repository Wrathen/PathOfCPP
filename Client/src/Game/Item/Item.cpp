#include "Item.h"
#include "LootableItem.h"
#include "../../Miscellaneous/Random.h"
#include "Currency/Currency.h"
#include "Equipment/Equipment.h"

// Static Methods
Item* Item::CreateRandomItem(int itemLevel) {
	ItemType itemType = RandomEnum(ItemType::Count);

	if (itemType == ItemType::Equipment) return Equipment::CreateRandomEquipment(itemLevel);
	else if (itemType == ItemType::Currency) return Currency::CreateRandomCurrency(itemLevel);
	return nullptr;
}
void Item::DropItem(int itemLevel, Vector2 pos) {
	LootableItem* loot = new LootableItem(CreateRandomItem(itemLevel));
	loot->transform.SetPosition(pos);
}