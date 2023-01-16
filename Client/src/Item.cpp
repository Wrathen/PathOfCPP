#include "Item.h"
#include "LootableItem.h"

// Static Methods
void Item::DropItem(Vector2 pos) {
	LootableItem* loot = new LootableItem();
	loot->transform.SetPosition(pos);
}