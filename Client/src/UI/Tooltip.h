#pragma once
#include "UIElement.h"
#include "../Game/Item/Item.h"
#include "../Components/TextRenderer.h"

class Tooltip : public UIElement {
	Item* item = nullptr;
	TextRenderer text_name;
	TextRenderer text_mods;
	TextRenderer text_description;

public:
	Tooltip();

	void SetItem(Item* _item);

	void Start() override;
	void Update() override;
	void Render() override;

	void OnDelete() override {}

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};