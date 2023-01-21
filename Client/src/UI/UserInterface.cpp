#include "UserInterface.h"
#include "../Managers/GameManager.h"

void UserInterface::Init() {
	xpBar = new XPBar();
	currencyBar = new CurrencyBar();
	tooltip = new Tooltip();
}
void UserInterface::Update() {
	if (!player) { player = GAME.GetPlayer(); return; }

	UpdateGold(player->goldAmount);
	UpdateXP(player->stats->GetXP());
	UpdateMaxXP(player->stats->GetMaxXP());
	UpdateLevel(player->stats->GetLevel());

	tooltip->Render();
	xpBar->Render();
	currencyBar->Render();
}

void UserInterface::UpdateGold(float value) { currencyBar->SetGold(value); }
void UserInterface::UpdateXP(float value) { xpBar->SetXP(value); }
void UserInterface::UpdateMaxXP(float value) { xpBar->SetMaxXP(value); }
void UserInterface::UpdateLevel(int value) { xpBar->SetLevel(value); }
void UserInterface::UpdateTooltip(Item* item) { tooltip->SetItem(item); }
void UserInterface::UpdateEquipment() {}
void UserInterface::UpdateInventory() {}

void UserInterface::ShowTooltip() { tooltip->SetVisible(true); }
void UserInterface::ShowInventory() {}
void UserInterface::ShowEquipment() {}
void UserInterface::ShowXPBar() { xpBar->SetVisible(true); }
void UserInterface::ShowGold() { currencyBar->SetVisible(true); }
void UserInterface::HideTooltip() { tooltip->SetVisible(false); }
void UserInterface::HideInventory() {}
void UserInterface::HideEquipment() {}
void UserInterface::HideXPBar() { xpBar->SetVisible(false); }
void UserInterface::HideGold() { currencyBar->SetVisible(false); }