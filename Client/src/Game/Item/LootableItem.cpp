#include "LootableItem.h"
#include "../../UI/UserInterface.h"
#include "../../Managers/UIManager.h"

LootableItem::LootableItem(Item* _item) : item(_item) {
	renderer.SetPositionRelative();
	renderer.AssignTexture(item->texturePath);
}

void LootableItem::Loot() {
	item->OnLoot();
	Delete();
}
bool LootableItem::OnClick() {
	Loot();
	return isBlockingRaycasts;
}

void LootableItem::OnDelete() {
	if (UIMgr.currentHoveredElement == this) {
		UIMgr.currentHoveredElement = nullptr;
		UI.UpdateTooltip(nullptr);
	}

	if (!item) return;
	item->OnDelete();
	delete item;
}
void LootableItem::OnMouseEnter() { UI.UpdateTooltip(item); }
void LootableItem::OnMouseOver() {}
void LootableItem::OnMouseLeave() { UI.UpdateTooltip(nullptr); }