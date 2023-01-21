#pragma once
#include "../UI/UIElement.h"
#include "../Entities/Entity.h"
#include "Stats.h"
#include "Component.h"

class HealthBar : public Component, public UIElement {
public:
	Transform* sourceTransform = nullptr;
	Stats* stats = nullptr;

	SpriteRenderer bg_renderer;
	Vector2 offset;

	HealthBar();
	void Start() override;
	void Update() override;
	void Render() override;
	void OnDelete() override {}
	void OnMouseEnter() override {}
	void OnMouseOver() override {}
	void OnMouseLeave() override {}
};