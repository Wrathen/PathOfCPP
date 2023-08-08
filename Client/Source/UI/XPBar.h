#pragma once
#include "UIElement.h"
#include "../Components/TextRenderer.h"

class XPBar: public UIElement {
private:
	SpriteRenderer corners_renderer;
	SpriteRenderer background_renderer;
	// There is also 'renderer', which is the fronground renderer
	// Inheriting from UIElement
	TextRenderer levelText;

	float xp = -1;
	float maxXP = -1;
	int level = -1;

public:
	XPBar();
	void SetXP(float _xp);
	void SetMaxXP(float _maxXP);
	void SetLevel(int _level);

	void Start() override;
	void Update() override;
	void Render() override;

	void OnDelete() override {}

	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};