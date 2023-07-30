#include "UserInterface.h"
#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"

void UserInterface::Init() {
	xpBar = new XPBar();
	currencyBar = new CurrencyBar();
	fpsBar = new FPSBar();
	tooltip = new Tooltip();
	powerUpGroup = new PowerUpGroup();
}
void UserInterface::Update() {
	if (!player) { player = GAME.GetPlayer(); return; }

	UpdateGold(player->goldAmount);
	UpdateXP(player->CStats->GetXP());
	UpdateMaxXP(player->CStats->GetMaxXP());
	UpdateLevel(player->CStats->GetLevel());

	static Timer timer("FPSTimer");
	if (timer.GetTimeMS() > 250) {
		UpdateFPS(GAME.GetFPS());
		timer.Reset();
	}

	if (tooltip->GetVisible()) tooltip->Render();
	if (xpBar->GetVisible()) xpBar->Render();
	if (currencyBar->GetVisible()) currencyBar->Render();
	if (powerUpGroup->GetVisible()) powerUpGroup->Render();
	if (fpsBar->GetVisible()) fpsBar->Render();
}

void UserInterface::UpdateGold(float value) { currencyBar->SetGold(value); }
void UserInterface::UpdateXP(float value) { xpBar->SetXP(value); }
void UserInterface::UpdateMaxXP(float value) { xpBar->SetMaxXP(value); }
void UserInterface::UpdateLevel(int value) { xpBar->SetLevel(value); }
void UserInterface::UpdateFPS(int value) { fpsBar->SetFPS(value); }
void UserInterface::UpdateTooltip(Item* item) { tooltip->SetItem(item); }
void UserInterface::UpdateEquipment() {}
void UserInterface::UpdateInventory() {}
void UserInterface::UpdatePowerUps() { powerUpGroup->GeneratePowerUps(); }

void UserInterface::ShowTooltip() { tooltip->SetVisible(true); }
void UserInterface::ShowInventory() {}
void UserInterface::ShowEquipment() {}
void UserInterface::ShowXPBar() { xpBar->SetVisible(true); }
void UserInterface::ShowGold() { currencyBar->SetVisible(true); }
void UserInterface::ShowPowerUps() { InputMgr.DisableMouse(0.5f); powerUpGroup->SetVisible(true); }

void UserInterface::HideTooltip() { tooltip->SetVisible(false); }
void UserInterface::HideInventory() {}
void UserInterface::HideEquipment() {}
void UserInterface::HideXPBar() { xpBar->SetVisible(false); }
void UserInterface::HideGold() { currencyBar->SetVisible(false); }
void UserInterface::HidePowerUps() { powerUpGroup->SetVisible(false); }

void UserInterface::ClearPowerUps() { powerUpGroup->Clear(); }