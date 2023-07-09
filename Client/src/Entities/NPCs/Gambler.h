#pragma once
#include "NPC.h"

class Gambler: public NPC {
public:
	Gambler(std::string name);

	void Update() override;
	void OnPlayerNearby() override;
	void OnPlayerAway() override;

	void PurchaseRandomItem();
};