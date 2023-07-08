#pragma once
#include "UIElement.h"
#include "../Components/TextRenderer.h"

class SceneTitleBar : public UIElement {
	TextRenderer titleText;

public:
	SceneTitleBar();
	void SetTitle(std::string title);

	void Start() override;
	void Update() override;
	void Render() override;

	void OnDelete() override {}

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};