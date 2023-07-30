#pragma once
#include "../Item.h"

enum class CurrencyType {
	Gold = 0,
	Count
};

class Currency: public Item {
public:
	CurrencyType currencyType = CurrencyType::Gold;
	int amount = 0;

	// Constructors & Deconstructors
	Currency();
	Currency(CurrencyType _currencyType);

	// Main Functions
	std::string GetName() override;
	std::string GetDescription() override;
	std::string GetModsText() override;

	// Events
	virtual void OnDelete() override;
	virtual void OnLoot() override;
	virtual void OnUse() override;

	// Static Functions
	static Currency* CreateRandomCurrency(int itemLevel, unsigned int seed = 0);
};