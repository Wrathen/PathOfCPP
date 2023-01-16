#include "LootableItem.h"

LootableItem::LootableItem() : UIElement() {
	renderer.SetPositionRelative();
}
void LootableItem::Loot() {
	Debug("Hey I clicked this!");
}
bool LootableItem::OnClick() {
	Loot();
	return isBlockingRaycasts;
}