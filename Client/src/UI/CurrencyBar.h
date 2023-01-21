#pragma once
#include "UIElement.h"
#include "../Components/TextRenderer.h"

class CurrencyBar: public UIElement {
private:
	TextRenderer goldText;
	int gold = -1;

public:
	CurrencyBar();

	void SetGold(int _gold);

	void Start() override;
	void Update() override;
	void Render() override;

	void OnDelete() override {};

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};