#pragma once
#include "UIElement.h"
#include "../Components/TextRenderer.h"

class FPSBar : public UIElement
{
private:
	TextRenderer fpsText;

public:
	FPSBar();

	void SetFPS(int FPS);

	void Start() override;
	void Update() override;
	void Render() override;

	void OnDelete() override {};

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};