#include "Currency.h"
#include "../../../Miscellaneous/Random.h"
#include "../../../Managers/GameManager.h"

// Constructors & Deconstructors
Currency::Currency() {
	type = ItemType::Currency;
	currencyType = CurrencyType::Gold;
}
Currency::Currency(CurrencyType _currencyType) : Currency() {
	// Will notify me that I need to change here when I add more types.
	static_assert((int)CurrencyType::Count == 1);

	currencyType = _currencyType;
	texturePath = _currencyType == CurrencyType::Gold ? "assets/sprites/Item/Currency/0.png" : "";

	name = _currencyType == CurrencyType::Gold ? "Gold" : "Unnamed Coin";
}

Currency* Currency::CreateRandomCurrency(int itemLevel, unsigned int seed) {
	CurrencyType currencyType = RandomEnum(CurrencyType::Count);
	Currency* currency = new Currency(currencyType);
	currency->amount = itemLevel;

	return currency;
}

std::string Currency::GetName() { return std::to_string(amount) + " " + name; }
std::string Currency::GetDescription() { return "Every human loves the economy.\nThis shall help you get higher\n in the hierarchy."; }
std::string Currency::GetModsText() { return ""; }

// Events
void Currency::OnDelete() {}
void Currency::OnLoot() {
	if (currencyType == CurrencyType::Gold)
		GAME.GetPlayer()->goldAmount += amount;
}
void Currency::OnUse() {}