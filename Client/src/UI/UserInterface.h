#pragma once
#include "../Miscellaneous/Singleton.h"
#include "../Entities/Player.h"
#include "XPBar.h"
#include "CurrencyBar.h"
#include "Tooltip.h"
#include "PowerUpGroup.h"

#define UI UserInterface::GetInstance()
class UserInterface : public Singleton<UserInterface> { friend class Singleton;
public:
	Player* player = nullptr;
	XPBar* xpBar = nullptr;
	CurrencyBar* currencyBar = nullptr;
	Tooltip* tooltip = nullptr;
	PowerUpGroup* powerUpGroup = nullptr;

	void Init();
	void Update();

	void UpdateGold(float value);
	void UpdateXP(float value);
	void UpdateMaxXP(float value);
	void UpdateLevel(int value);
	void UpdateTooltip(Item* item);
	void UpdateEquipment();
	void UpdateInventory();
	void UpdatePowerUps();

	void ShowTooltip();
	void ShowInventory();
	void ShowEquipment();
	void ShowXPBar();
	void ShowGold();
	void ShowPowerUps();

	void HideTooltip();
	void HideInventory();
	void HideEquipment();
	void HideXPBar();
	void HideGold();
	void HidePowerUps();

	void ClearPowerUps();

private:
	UserInterface() {}
	~UserInterface() {}
	UserInterface(UserInterface const&) = delete;
	void operator=(UserInterface const&) = delete;
};