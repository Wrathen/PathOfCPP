#include "UserInterface.h"
#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include "../Game/Item/Equipment/Equipment.h"

void UserInterface::Init() {
	xpBar = new XPBar();
	currencyBar = new CurrencyBar();
	fpsBar = new FPSBar();
	tooltip = new Tooltip();
	powerUpGroup = new PowerUpGroup();
	inventory = new Inventory();
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

	if (xpBar->GetVisible()) xpBar->Render();
	if (currencyBar->GetVisible()) currencyBar->Render();
	if (powerUpGroup->GetVisible()) powerUpGroup->Render();
	if (fpsBar->GetVisible()) fpsBar->Render();
	if (inventory->GetVisible()) inventory->Render();
	if (tooltip->GetVisible()) tooltip->Render();

	if (InputMgr.IsKeyPressed(SDLK_g))
		for (int i = 0; i < 8; ++i)
			inventory->Add(new UIItem(Equipment::CreateRandomEquipment(RandomInt(30, 300))));
	if (InputMgr.IsKeyPressed(SDLK_b))
		(inventory->GetVisible() ? HideInventory(): ShowInventory());		
}

void UserInterface::UpdateGold(float value) { currencyBar->SetGold(value); }
void UserInterface::UpdateXP(float value) { xpBar->SetXP(value); }
void UserInterface::UpdateMaxXP(float value) { xpBar->SetMaxXP(value); }
void UserInterface::UpdateLevel(int value) { xpBar->SetLevel(value); }
void UserInterface::UpdateFPS(int value) { fpsBar->SetFPS(value); }
void UserInterface::UpdateTooltip(UIElement* target, Item* item, TooltipPositionType positionType) { tooltip->SetItem(target, item, positionType); }
void UserInterface::UpdateEquipment() {}
void UserInterface::UpdateInventory() {}
void UserInterface::UpdatePowerUps() { powerUpGroup->GeneratePowerUps(); }

void UserInterface::ShowTooltip() { tooltip->SetVisible(true); }
void UserInterface::ShowInventory() { inventory->SetVisible(true); }
void UserInterface::ShowEquipment() {}
void UserInterface::ShowXPBar() { xpBar->SetVisible(true); }
void UserInterface::ShowGold() { currencyBar->SetVisible(true); }
void UserInterface::ShowPowerUps() { InputMgr.DisableMouse(0.5f); powerUpGroup->SetVisible(true); }

void UserInterface::HideTooltip() { tooltip->SetVisible(false); }
void UserInterface::HideInventory() { inventory->SetVisible(false); }
void UserInterface::HideEquipment() {}
void UserInterface::HideXPBar() { xpBar->SetVisible(false); }
void UserInterface::HideGold() { currencyBar->SetVisible(false); }
void UserInterface::HidePowerUps() { powerUpGroup->SetVisible(false); }

void UserInterface::ClearPowerUps() { powerUpGroup->Clear(); }