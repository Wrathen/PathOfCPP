#pragma once
#include <vector>
#include "UIElement.h"
#include "../Game/PowerUp/PowerUp.h"

class PowerUpGroup: public UIElement {
public:
	PowerUp* power1 = nullptr;
	PowerUp* power2 = nullptr;
	PowerUp* power3 = nullptr;

	PowerUpGroup();

	// Generates random powerups
	void GeneratePowerUps();
	std::vector<UIElement*> GetCurrentShownPowerUps();

	// Clears generated Powerups
	void Clear();

	void Start() override {};
	void Update() override {};
	void Render() override;

	void OnDelete() override {}

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};